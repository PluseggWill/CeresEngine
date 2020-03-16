#pragma once


#include <DirectXMath.h>

using namespace DirectX;

class Rigidbody {
public:
	XMVECTOR velocity;
	XMVECTOR angularVelocity;
	float mass;
	bool usingGravity;

	void AddForce(XMVECTOR force);
	void AddAngularForce(XMVECTOR force);

};