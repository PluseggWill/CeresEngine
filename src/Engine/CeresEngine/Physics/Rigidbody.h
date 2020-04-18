#pragma once


#include <DirectXMath.h>
#include "../Core/GameComponent.h"
#include "Collider.h"

using namespace DirectX;

class Rigidbody : public GameComponent {
public:
	XMVECTOR center;
	XMVECTOR velocity;
	XMVECTOR angularVelocity;
	float mass;
	float bounciness;
	bool isStatic;
	bool isLockPosition;
	bool isLockRotation;

	void AddForce(XMVECTOR force);
	void AddAngularForce(XMVECTOR force);
	void AddForceAtPoint(XMVECTOR force, XMVECTOR point);

	void Update(float deltaTime, Collider* collider);

};