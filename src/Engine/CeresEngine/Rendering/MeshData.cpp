#include "MeshData.h"

void MeshData::ComputeNormal()
{
	for (UINT i = 0; i < mIndices.size() / 3; ++i)
	{

		// indices of the ith triangle
		UINT i0 = mIndices[i * 3 + 0];
		UINT i1 = mIndices[i * 3 + 1];
		UINT i2 = mIndices[i * 3 + 2];

		// vertices of ith triangle
		Vertex v0 = mVertices[i0];
		Vertex v1 = mVertices[i1];
		Vertex v2 = mVertices[i2];

		// compute face normal
		XMVECTOR vec0 = XMLoadFloat3(&v0.Position);
		XMVECTOR vec1 = XMLoadFloat3(&v1.Position);
		XMVECTOR vec2 = XMLoadFloat3(&v2.Position);
		XMVECTOR e0 = XMVectorSubtract(vec1, vec0);
		XMVECTOR e1 = XMVectorSubtract(vec2, vec0);
		XMVECTOR faceNormal = XMVector3Cross(e0, e1);

		// add this face normal to vertex
		XMVECTOR n0 = XMLoadFloat3(&v0.Normal);
		XMVECTOR n1 = XMLoadFloat3(&v1.Normal);
		XMVECTOR n2 = XMLoadFloat3(&v2.Normal);
		n0 = XMVectorAdd(n0, faceNormal);
		n1 = XMVectorAdd(n1, faceNormal);
		n2 = XMVectorAdd(n2, faceNormal);

		XMStoreFloat3(&mVertices[i0].Normal, n0);
		XMStoreFloat3(&mVertices[i1].Normal, n1);
		XMStoreFloat3(&mVertices[i2].Normal, n2);
	}

	// normalize the normal
	for (UINT i = 0; i < mVertices.size(); ++i)
	{
		XMVECTOR n = XMLoadFloat3(&mVertices[i].Normal);
		XMStoreFloat3(&mVertices[i].Normal, XMVector3Normalize(n));
	}
}

void MeshData::AddNumTriangles(UINT num)
{
	mNumTriangles += num;
}
