#include "Collider.h"
#include <stdio.h>

void Collider::SetCenter(XMVECTOR xy)
{
	this->center = xy;
}

void Collider::SetCenter(float x, float y)
{
	this->center = XMVectorSetX(this->center, x);
	this->center = XMVectorSetY(this->center, y);
}

void Collider::SetRotateMatrix(XMMATRIX rm)
{
	this->rotateMatrix = rm;
}

XMVECTOR Collider::GetCenter() const
{
	return this->center;
}

XMMATRIX Collider::GetRotateMatrix() const
{
	return this->rotateMatrix;
}

BoxCollider::BoxCollider()
{
	this->size = XMVectorSet(1, 1, 1, 0);
	this->offset = XMVectorSet(0, 0, 0, 0);
}

BoxCollider::BoxCollider(float x, float y)
{
	this->size = XMVectorSet(x, y, 1, 0);
	this->offset = XMVectorSet(0, 0, 0, 0);
}

BoxCollider::BoxCollider(XMVECTOR size, XMVECTOR offset)
{
	this->size = size;
	this->offset = offset;
}

BoxCollider::~BoxCollider()
{
}

XMVECTOR BoxCollider::GetSize() const
{
	return this->size;
}

XMVECTOR BoxCollider::GetOffset() const
{
	return this->offset;
}

void BoxCollider::SetSize(float x, float y)
{
	this->size = XMVectorSet(x, y, 1, 0);
}

void BoxCollider::SetSize(XMVECTOR xy)
{
	this->size = xy;
}

void BoxCollider::SetOffset(float x, float y)
{
	this->offset = XMVectorSet(x, y, 1, 0);
}

void BoxCollider::SetOffset(XMVECTOR xy)
{
	this->offset = xy;
}

CircleCollider::CircleCollider()
{
	this->radius = 1.0f;
	this->offset = XMVectorSet(0, 0, 0, 0);
}

CircleCollider::CircleCollider(float radius)
{
	this->radius = radius;
	this->offset = XMVectorSet(0, 0, 0, 0);
}

CircleCollider::CircleCollider(float radius, XMVECTOR offset)
{
	this->radius = radius;
	this->offset = offset;
}

CircleCollider::~CircleCollider()
{
}

float CircleCollider::GetRadius() const
{
	return radius;
}

XMVECTOR CircleCollider::GetOffset() const
{
	return offset;
}

void CircleCollider::SetRadius(float radius)
{
	this->radius = radius;
}

void CircleCollider::SetOffset(float x, float y)
{
	this->offset = XMVectorSet(x, y, 0, 0);
}

void CircleCollider::SetOffset(XMVECTOR xy)
{
	this->offset = xy;
}


