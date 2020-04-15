#include "Rigidbody.h"
#include "PhysicsGeneralMethods.h"
#include <stdio.h>
#define M_PI 3.14159265358979323846

using namespace Physics;

void Rigidbody::AddForce(XMVECTOR force)
{
	velocity = XMVectorAdd(velocity, XMVectorScale(force, 1 / mass));
}

void Rigidbody::AddAngularForce(XMVECTOR force)
{
	angularVelocity = XMVectorAdd(angularVelocity, XMVectorScale(force, 1 / mass));
}

void Rigidbody::AddForceAtPoint(XMVECTOR force, XMVECTOR point)
{
	//force /= 1000;
	XMVECTOR n = center - point;
	float powl = XMVectorGetX(n) * XMVectorGetX(n) + XMVectorGetY(n) * XMVectorGetY(n);
	XMVECTOR vforce = force * n * n / powl;
	XMVECTOR aforce = force - vforce;
	float afl = sqrtf(XMVectorGetX(aforce) * XMVectorGetX(aforce) + XMVectorGetY(aforce) * XMVectorGetY(aforce))/5;
	if (IsThreePointUnclockwise(XMVectorGetX(center), XMVectorGetY(center), XMVectorGetX(point), XMVectorGetY(point), XMVectorGetX(point) + XMVectorGetX(aforce), XMVectorGetY(point) + XMVectorGetY(aforce))) {
		AddAngularForce(XMVectorSet(0, 0, -afl, 0));
	}
	else {
		AddAngularForce(XMVectorSet(0, 0, +afl, 0));
	}
	//printf("%f,%f\n", XMVectorGetX(aforce), XMVectorGetY(aforce));
	//AddForce(vforce);
	AddAngularForce(aforce);
}

void Rigidbody::Update(float deltaTime, Collider* collider)
{
	if (isStatic) {
		return;
	}
	if (!isLockPosition) {
		collider->SetCenter(collider->GetCenter() + velocity * deltaTime);
		center = collider->GetCenter();
	}
	if (!isLockRotation) {
		collider->SetRotateMatrix(XMMatrixMultiply(collider->GetRotateMatrix(), XMMatrixTranspose(XMMatrixRotationRollPitchYaw(0, 0, deltaTime * XMVectorGetZ(angularVelocity) * M_PI / 180))));
	}
}
