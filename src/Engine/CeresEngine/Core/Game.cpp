#include "Game.h"
#include "../Rendering/Vertex.h"
#include "../GameObject.h"
#include "../Collider.h"
#include "../Rigidbody.h"
#include "../PhysicsGeneralMethods.h"

#define _USE_MATH_DEFINES
#include <math.h>

// For the DirectX Math library
using namespace DirectX;
using namespace Physics;

BoxCollider* bc = new BoxCollider(0.3f, 0.3f);
BoxCollider* bc2 = new BoxCollider(0.4f, 2);
CircleCollider* cc = new CircleCollider(1);
CircleCollider* cc2 = new CircleCollider(1);

Rigidbody* rb = new Rigidbody();
Rigidbody* rb2 = new Rigidbody();

bool lastOverlapping = false;

bool isChangingColor = false;


// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Release any (and all!) DirectX objects
	// we've made in the Game class
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();

	bc->SetCenter(2, 0);
	bc2->SetCenter(0, 0);
	bc2->SetOffset(0, 0.8f);
	cc->SetCenter(1.51f, 0); 
	cc2->SetCenter(2.1f, 0);
	rb->mass = 1;
	rb2->mass = 3;
	rb2->AddAngularForce(XMVectorSet(0, 0, 40, 0));
	//bc2->SetRotateMatrix(XMMatrixMultiply(bc2->GetRotateMatrix(), XMMatrixTranspose(XMMatrixRotationRollPitchYaw(0, 0, 45 * M_PI / 180))));
	
	/*XMFLOAT2 p1, p2, p3, p4;
	p1.x = 0;
	p1.y = 0;
	p2.x = 2;
	p2.y = 0;
	p3.x = 0;
	p3.y = -1;
	p4.x = 2;
	p4.y = 1;
	XMFLOAT2 result;
	bool isIntersecting = IsTwoLineIntersecting(p1, p2, p3, p4, result);;
	if (isIntersecting) {
		printf("\nJJJ\n");
	}
	else {
		printf("\nNNN\n");
	}*/

	//printf("\n%f\n", PointToInfinityLineDistance(4, 1.5, 1, 0, 2, 0));

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex vertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), green },
	};

	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	int indices[] = { 0, 1, 2 };


	// Create the VERTEX BUFFER description -----------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 3;       // 3 = number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);



	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * 3;         // 3 = number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);
}

void Game::CreateTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6, float x7, float y7, float x8, float y8)
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	if (isChangingColor) {
		blue = blue = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex vertices[] =
	{
		{ XMFLOAT3(x1, y1, +0.0f), blue },
		{ XMFLOAT3(x2, y2, +0.0f), blue },
		{ XMFLOAT3(x3, y3, +0.0f), blue },
		{ XMFLOAT3(x4, y4, +0.0f), blue },
		{ XMFLOAT3(x5, y5, +0.0f), blue },
		{ XMFLOAT3(x6, y6, +0.0f), blue },
		{ XMFLOAT3(x7, y7, +0.0f), blue },
		{ XMFLOAT3(x8, y8, +0.0f), blue },
	};

	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	int indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7 };


	// Create the VERTEX BUFFER description -----------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;       // 3 = number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);



	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * 12;         // 3 = number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);
}

void Game::CreateRectangle(float x, float y, float sizeX, float sizeY)
{
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	if (GetAsyncKeyState(VK_UP)) {
		rb->velocity = XMVectorSetY(rb->velocity, 1.8f);
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		rb->velocity = XMVectorSetY(rb->velocity, -1.8f);
	}
	else {
		rb->velocity = XMVectorSetY(rb->velocity, 0);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		rb->velocity = XMVectorSetX(rb->velocity, 1.8f);
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		rb->velocity = XMVectorSetX(rb->velocity, -1.8f);
	}
	else {
		rb->velocity = XMVectorSetX(rb->velocity, 0);
	}

	bc->SetCenter(bc->GetCenter() + rb->velocity * deltaTime);
	rb->center = bc->GetCenter();
	bc2->SetCenter(bc2->GetCenter() + rb2->velocity * deltaTime);
	rb2->center = bc2->GetCenter();

	XMVECTOR point;
	bool isOverlapping = IsOverlapping(*bc, *bc2, point);
	//printf("%f,%f\n", XMVectorGetX(point), XMVectorGetY(point));
	if (!lastOverlapping && isOverlapping) {
		isChangingColor = true;
		printf("\nOnCollisionEnter\n");
	}
	if (lastOverlapping && !isOverlapping) {
		isChangingColor = false;
		printf("\nOnCollisionExit\n");
	}
	if (isOverlapping) {
		HandleCollisionForRigidbody(rb, bc, bc2, point);
		float f = rb2->mass * powf(XMVectorGetZ(rb2->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(point), XMVectorGetY(point), XMVectorGetX(bc2->GetCenter()), XMVectorGetY(bc2->GetCenter())));
		XMVECTOR force = XMVector2Normalize(bc->GetCenter() - point) * f;
		
		force = XMVectorSetZ(force, 0);
		printf("force: %f, %f, %f ,%f\n",f, XMVectorGetX(force), XMVectorGetY(force), XMVectorGetZ(force));
		rb2->AddForceAtPoint(rb->velocity - force,point);
		//rb->AddForceAtPoint(rb2->velocity, point);
		//rb->AddForceAtPoint(rb2->velocity, point);
	}
	lastOverlapping = isOverlapping;
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	vertexShader->SetMatrix4x4("world", worldMatrix);
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	vertexShader->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	vertexShader->SetShader();
	pixelShader->SetShader();

	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	XMVECTOR points1[4], points2[4];
	points1[0] = XMVectorSet(XMVectorGetX(bc->GetCenter()) + XMVectorGetX(bc->GetSize()) / 2, XMVectorGetY(bc->GetCenter()) + XMVectorGetY(bc->GetSize()) / 2, 0, 0);
	points1[1] = XMVectorSet(XMVectorGetX(bc->GetCenter()) + XMVectorGetX(bc->GetSize()) / 2, XMVectorGetY(bc->GetCenter()) - XMVectorGetY(bc->GetSize()) / 2, 0, 0);
	points1[2] = XMVectorSet(XMVectorGetX(bc->GetCenter()) - XMVectorGetX(bc->GetSize()) / 2, XMVectorGetY(bc->GetCenter()) - XMVectorGetY(bc->GetSize()) / 2, 0, 0);
	points1[3] = XMVectorSet(XMVectorGetX(bc->GetCenter()) - XMVectorGetX(bc->GetSize()) / 2, XMVectorGetY(bc->GetCenter()) + XMVectorGetY(bc->GetSize()) / 2, 0, 0);
	points2[0] = XMVectorSet(XMVectorGetX(bc2->GetCenter()) + XMVectorGetX(bc2->GetSize()) / 2, XMVectorGetY(bc2->GetCenter()) + XMVectorGetY(bc2->GetSize()) / 2, 0, 0);
	points2[1] = XMVectorSet(XMVectorGetX(bc2->GetCenter()) + XMVectorGetX(bc2->GetSize()) / 2, XMVectorGetY(bc2->GetCenter()) - XMVectorGetY(bc2->GetSize()) / 2, 0, 0);
	points2[2] = XMVectorSet(XMVectorGetX(bc2->GetCenter()) - XMVectorGetX(bc2->GetSize()) / 2, XMVectorGetY(bc2->GetCenter()) - XMVectorGetY(bc2->GetSize()) / 2, 0, 0);
	points2[3] = XMVectorSet(XMVectorGetX(bc2->GetCenter()) - XMVectorGetX(bc2->GetSize()) / 2, XMVectorGetY(bc2->GetCenter()) + XMVectorGetY(bc2->GetSize()) / 2, 0, 0);


	bc->SetRotateMatrix(XMMatrixMultiply(bc->GetRotateMatrix(), XMMatrixTranspose(XMMatrixRotationRollPitchYaw(0, 0, deltaTime * XMVectorGetZ(rb->angularVelocity) * M_PI / 180))));
	bc2->SetRotateMatrix(XMMatrixMultiply(bc2->GetRotateMatrix(), XMMatrixTranspose(XMMatrixRotationRollPitchYaw(0, 0, deltaTime * XMVectorGetZ(rb2->angularVelocity) * M_PI / 180))));

	for (int i = 0; i < 4; i++) {
		points1[i] -= bc->GetCenter();
		points2[i] -= bc2->GetCenter();
		points1[i] = XMVector2Transform(points1[i], bc->GetRotateMatrix());
		points2[i] = XMVector2Transform(points2[i], bc2->GetRotateMatrix());
		points1[i] += bc->GetCenter();
		points2[i] += bc2->GetCenter();
		XMVECTOR or1 = bc->GetOffset();
		XMVECTOR or2 = bc2->GetOffset();
		or1 = XMVector2Transform(or1, bc->GetRotateMatrix());
		or2 = XMVector2Transform(or2, bc2->GetRotateMatrix());

		points1[i] += or1;
		points2[i] += or2;
	}

	CreateTriangle(XMVectorGetX(points1[0]), XMVectorGetY(points1[0]), XMVectorGetX(points1[1]), XMVectorGetY(points1[1]), XMVectorGetX(points1[2]), XMVectorGetY(points1[2]), XMVectorGetX(points1[3]), XMVectorGetY(points1[3]), XMVectorGetX(points2[0]), XMVectorGetY(points2[0]), XMVectorGetX(points2[1]), XMVectorGetY(points2[1]), XMVectorGetX(points2[2]), XMVectorGetY(points2[2]), XMVectorGetX(points2[3]), XMVectorGetY(points2[3]));

	// Finally do the actual drawing
	//  - Do this ONCE PER OBJECT you intend to draw
	//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
	//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
	//     vertices in the currently set VERTEX BUFFER
	context->DrawIndexed(
		12,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices



	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion