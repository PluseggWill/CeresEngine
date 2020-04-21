#pragma once
#include "Vertex.h"
class MeshData
{
public:
	std::vector<Vertex> mVertices;
	std::vector<UINT> mIndices;

private:
	UINT mNumTriangles;

public:
	void ComputeNormal();
	void AddNumTriangles(UINT num);
};

