#include "Rigidbody.h"

void Rigidbody::AddForce(XMVECTOR force)
{
	velocity = XMVectorAdd(velocity, XMVectorScale(force, 1 / mass));
}

void Rigidbody::AddAngularForce(XMVECTOR force)
{
	angularVelocity = XMVectorAdd(angularVelocity, XMVectorScale(force, 1 / mass));
}
