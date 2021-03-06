#pragma once

#include "DXCore.h"
#include "../Rendering/SimpleShader.h"
#include <DirectXMath.h>
#include "..//Rendering/Vertex.h"
#include <D3DX11tex.h>
#include <vector>
#include "Scene.h"
#include "..//Rendering/Camera.h"
#include "..//Rendering/MeshData.h"
#include "..//Rendering/Light.h"

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:
	// Scenes to be loaded
	Scene* currentScene;
	//UINT currentScene;
	MeshData tempMeshData;

	// Current camera
	Camera* currentCamera;
	// Directional light
	DirectionalLight dirLight;
	Material mat;
	// Texture
	ID3D11ShaderResourceView* texture;
	ID3D11SamplerState* texSamplerState;

	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

public:
	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders();
	void CreateMatricesManually();
	void CreateGeometry();
	
	void InitCamera();
	void UpdateCamera();
	void SetLight();
	void InitTexture();
	void LoadScene(UINT numOfScene);
	void AddScene(Scene scene);
};

