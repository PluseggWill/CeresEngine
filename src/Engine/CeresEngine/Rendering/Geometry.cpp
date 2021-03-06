#include "Geometry.h"
 
void Geometry::CreateBox(float width, float height, float depth, XMFLOAT4 color, MeshData& meshData)
{

	// Box vertices

	Vertex v[24];

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	// 6 faces
	// Fill in the front face vertex data.
	v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, color.x, color.y, color.z, color.w, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	// Test code
	/*v[0] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[1] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[2] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[3] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);*/


	meshData.mVertices.assign(&v[0], &v[24]);

	// Create the indices

	UINT i[36];

	// Front
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Back
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Top
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Bottom
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Left
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Right
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	meshData.mIndices.assign(&i[0], &i[36]);
	meshData.AddNumTriangles(12);
}

void Geometry::CreateSphere(float radius, UINT sliceCount, UINT stackCount, XMFLOAT4 color, MeshData& meshData)
{
	meshData.mVertices.clear();
	meshData.mIndices.clear();

	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	meshData.mVertices.push_back( topVertex );

	float phiStep   = XM_PI/stackCount;
	float thetaStep = 2.0f*XM_PI/sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for(UINT i = 1; i <= stackCount-1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for(UINT j = 0; j <= sliceCount; ++j)
		{
			float theta = j*thetaStep;

			Vertex v;

			// spherical to cartesian
			v.Position.x = radius*sinf(phi)*cosf(theta);
			v.Position.y = radius*cosf(phi);
			v.Position.z = radius*sinf(phi)*sinf(theta);

			// Partial derivative of P with respect to theta
			v.TangentU.x = -radius*sinf(phi)*sinf(theta);
			v.TangentU.y = 0.0f;
			v.TangentU.z = +radius*sinf(phi)*cosf(theta);

			XMVECTOR T = XMLoadFloat3(&v.TangentU);
			XMStoreFloat3(&v.TangentU, XMVector3Normalize(T));

			XMVECTOR p = XMLoadFloat3(&v.Position);
			XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

			v.TexC.x = theta / XM_2PI;
			v.TexC.y = phi / XM_PI;

			meshData.mVertices.push_back( v );
		}
	}

	meshData.mVertices.push_back( bottomVertex );

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for(UINT i = 1; i <= sliceCount; ++i)
	{
		meshData.mIndices.push_back(0);
		meshData.mIndices.push_back(i+1);
		meshData.mIndices.push_back(i);
	}
	
	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount+1;
	for(UINT i = 0; i < stackCount-2; ++i)
	{
		for(UINT j = 0; j < sliceCount; ++j)
		{
			meshData.mIndices.push_back(baseIndex + i*ringVertexCount + j);
			meshData.mIndices.push_back(baseIndex + i*ringVertexCount + j+1);
			meshData.mIndices.push_back(baseIndex + (i+1)*ringVertexCount + j);

			meshData.mIndices.push_back(baseIndex + (i+1)*ringVertexCount + j);
			meshData.mIndices.push_back(baseIndex + i*ringVertexCount + j+1);
			meshData.mIndices.push_back(baseIndex + (i+1)*ringVertexCount + j+1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	UINT southPoleIndex = (UINT)meshData.mVertices.size()-1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;
	
	for(UINT i = 0; i < sliceCount; ++i)
	{
		meshData.mIndices.push_back(southPoleIndex);
		meshData.mIndices.push_back(baseIndex+i);
		meshData.mIndices.push_back(baseIndex+i+1);
	}
}