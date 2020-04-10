#pragma once

#include <DirectXMath.h>
#include "Collider.h"

using namespace DirectX;
struct Ray
{
public:
	XMVECTOR point;
	XMVECTOR direction;
};

struct Line {
public:
	XMVECTOR startPoint;
	XMVECTOR endPoint;
};

struct HitInfo
{
public:
	Collider hitCollider;
	XMVECTOR hitPoint;
};


