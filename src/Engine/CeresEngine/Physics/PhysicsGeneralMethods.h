#pragma once

#include <DirectXMath.h>
#include <vector>
#include "../Core/GameComponent.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "..//Core/GameObject.h"
#include "Ray.h"

namespace Physics {
	bool IsOverlapping(BoxCollider c1, BoxCollider c2);
	bool IsOverlapping(BoxCollider c1, CircleCollider c2);
	bool IsOverlapping(CircleCollider c1, CircleCollider c2);
	bool IsOverlapping(BoxCollider c1, BoxCollider c2, XMVECTOR& result);
	bool IsOverlapping(BoxCollider c1, CircleCollider c2, XMVECTOR& result);
	bool IsOverlapping(CircleCollider c1, CircleCollider c2, XMVECTOR& result);

	bool IsTwoLineIntersecting(XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2 point3, XMFLOAT2 point4);
	bool IsTwoLineIntersecting(XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2 point3, XMFLOAT2 point4, XMFLOAT2& result);
	bool IsRayLineIntersecting(Ray ray, XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2& result);
	int IsLineCircleIntersecting(XMFLOAT2 point, float radius, XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2& result1, XMFLOAT2& result2);
	bool IsRayCircleIntersecting(XMFLOAT2 point, float radius, Ray ray, XMFLOAT2& result);


	XMFLOAT2 GetMiddlePointOfTwoMiddlePoints(XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2 point3, XMFLOAT2 point4);
	float PointToPointDistance(float x1, float y1, float x2, float y2);
	float PointToLineDistance(float x, float y, float x1, float y1, float x2, float y2);
	float PointToInfinityLineDistance(float x, float y, float x1, float y1, float x2, float y2);
	bool IsMiddleValuesOverlapping(float v1, float v2, float v3, float v4);
	bool IsBetweenTwoValues(float v, float v1, float v2);
	bool IsInDirectionOfTwoValues(float v, float v1, float v2);
	float AngleBetweenThreePoint(float x1, float y1, float x2, float y2, float x3, float y3);
	bool IsThreePointUnclockwise(float x1, float y1, float x2, float y2, float x3, float y3);

	bool RaycastCollider(Ray ray, BoxCollider targetCollider, HitInfo& result);
	bool RaycastCollider(Ray ray, CircleCollider targetCollider, HitInfo& result);
	bool LinecastCollider(Line line, BoxCollider targetCollider, HitInfo& result);
	bool LinecastCollider(Line line, CircleCollider targetCollider, HitInfo& result);
	
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, BoxCollider* targetCollider, XMVECTOR hitpoint);
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, BoxCollider* targetCollider, XMVECTOR hitpoint);
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, CircleCollider* targetCollider, XMVECTOR hitpoint);
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, CircleCollider* targetCollider, XMVECTOR hitpoint);
}