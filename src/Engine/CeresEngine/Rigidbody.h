#pragma once


#include <DirectXMath.h>
#include "GameComponent.h"

using namespace DirectX;

class Rigidbody : public GameComponent {
public:
	XMVECTOR center;
	XMVECTOR velocity;
	XMVECTOR angularVelocity;
	float mass;
	float bounciness;
	bool usingGravity;

	void AddForce(XMVECTOR force);
	void AddAngularForce(XMVECTOR force);
	void AddForceAtPoint(XMVECTOR force, XMVECTOR point);

};