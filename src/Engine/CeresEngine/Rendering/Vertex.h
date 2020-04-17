#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <Windows.h>

using namespace DirectX;

// --------------------------------------------------------
// A custom vertex definition
//
// You will eventually ADD TO this, and/or make more of these!
// --------------------------------------------------------
struct Vertex
{
	// TODO: UV
	Vertex() {}
	Vertex(const XMFLOAT3& p, const XMFLOAT3& n, 
		   const XMFLOAT3& t, const XMFLOAT2& uv)
		: Position(p), Normal(n), TangentU(t), TexC(uv) {}
	Vertex(
		float px, float py, float pz,
		float nx, float ny, float nz,
		float tx, float ty, float tz,
		float u, float v
		)
		: Position(px, py, pz), Normal(nx, ny, nz),
		TangentU(tx, ty, tz), TexC(u,v) {}
	XMFLOAT3 Position;	    // The position of the vertex
	//XMFLOAT4 Color;        // The color of the vertex
	XMFLOAT3 Normal;		// The normal of the vertex
	XMFLOAT3 TangentU;		// The Tangent vector of the vertex
	XMFLOAT2 TexC;			// The texture of the vertex
};

struct MeshData
{
	std::vector<Vertex> Vertices;
	std::vector<UINT> Indices;
};


