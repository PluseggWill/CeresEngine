#pragma once
#include <DirectXMath.h>
#include "GameComponent.h"

using namespace DirectX;
class Collider : public GameComponent
{
protected:
	XMVECTOR center;
	XMMATRIX rotateMatrix = XMMatrixIdentity();

public:
	void SetCenter(XMVECTOR xy);
	void SetCenter(float x, float y);
	void SetRotateMatrix(XMMATRIX rm);
	XMVECTOR GetCenter() const;
	XMMATRIX GetRotateMatrix() const;
};

class BoxCollider : public Collider {
private:
	XMVECTOR size;
	XMVECTOR offset;

public:
	BoxCollider();
	BoxCollider(float x, float y);
	BoxCollider(XMVECTOR size = { 1, 1 }, XMVECTOR offset = { 0, 0 });
	~BoxCollider();

	XMVECTOR GetSize() const;
	XMVECTOR GetOffset() const;

	void SetSize(float x, float y);
	void SetSize(XMVECTOR xy);
	void SetOffset(float x, float y);
	void SetOffset(XMVECTOR xy);
};

class CircleCollider : public Collider {
private:
	float radius;
	XMVECTOR offset;

public:
	CircleCollider();
	CircleCollider(float radius);
	CircleCollider(float radius, XMVECTOR offset);
	~CircleCollider();

	float GetRadius() const;
	XMVECTOR GetOffset() const;

	void SetRadius(float radius);
	void SetOffset(float x, float y);
	void SetOffset(XMVECTOR xy);
};

