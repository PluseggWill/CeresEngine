#include "Transform.h"

Transform::Transform()
{
	localPosition = XMVectorZero();
	localRotation = XMQuaternionIdentity();
	localScale = XMVectorSet(1, 1, 1, 0);

	parent = nullptr;
}

Transform::Transform(float x, float y, float z)
{
	localPosition = XMVectorSet(x, y, z, 0);
	localRotation = XMQuaternionIdentity();
	localScale = XMVectorSet(1, 1, 1, 0);

	parent = nullptr;
}

Transform::Transform(XMFLOAT3 position, XMFLOAT4 rotation, XMFLOAT3 scale)
{
	this->localPosition = XMLoadFloat3(&position);
	this->localRotation = XMLoadFloat4(&rotation);
	this->localScale = XMLoadFloat3(&scale);

	parent = nullptr;
}

Transform::Transform(XMVECTOR position, XMVECTOR rotation, XMVECTOR scale)
{
	this->localPosition = position;
	this->localRotation = rotation;
	this->localScale = scale;

	parent = nullptr;
}

Transform::~Transform()
{
}

XMVECTOR Transform::GetLocalPosition()
{
	return localPosition;
}

XMVECTOR Transform::GetPosition()
{
	return parent ? XMVector3Transform(localPosition, parent->GetWorldMatrix()) : localPosition;
}

XMVECTOR Transform::GetLocalRotation()
{
	return localRotation;
}

XMVECTOR Transform::GetRotation()
{
	return parent ? XMQuaternionMultiply(localRotation, parent->GetRotation()) : localRotation;
}

XMVECTOR Transform::GetLocalScale()
{
	return localScale;
}

XMVECTOR Transform::GetScale()
{
	return parent ? XMVectorMultiply(localScale, parent->GetScale()) : localScale;
}

XMMATRIX Transform::GetWorldMatrix()
{
	XMMATRIX worldMatrix;
	if (parent)
		worldMatrix = (XMMatrixScalingFromVector(localScale) * XMMatrixRotationQuaternion(localRotation) * XMMatrixTranslationFromVector(localPosition)) * parent->GetWorldMatrix();
	else
		worldMatrix = XMMatrixScalingFromVector(localScale) * XMMatrixRotationQuaternion(localRotation) * XMMatrixTranslationFromVector(localPosition);
	return worldMatrix;
}

XMVECTOR Transform::GetForwardVector()
{
	return XMVector3Normalize(XMVector3Rotate({ 0, 0, 1 }, GetRotation()));
}

Transform* Transform::GetParent()
{
	return parent;
}

Transform* Transform::GetChild(size_t index)
{
	return index < children.size() ? children[index] : nullptr;
}

size_t Transform::GetChildCount()
{
	return children.size();
}

void Transform::SetLocalPosition(float x, float y, float z)
{
}

void Transform::SetLocalPosition(XMFLOAT3 position)
{
}

void Transform::SetLocalPosition(XMVECTOR position)
{
}

void Transform::SetPosition(float x, float y, float z)
{
}

void Transform::SetPosition(XMFLOAT3 position)
{
}

void Transform::SetPosition(XMVECTOR position)
{
}

void Transform::SetLocalRotation(float x, float y, float z)
{
}

void Transform::SetLocalRotation(XMFLOAT4 rotation)
{
}

void Transform::SetLocalRotation(XMVECTOR rotation)
{
}

void Transform::SetRotation(float x, float y, float z)
{
}

void Transform::SetRotation(XMFLOAT4 rotation)
{
}

void Transform::SetRotation(XMVECTOR rotation)
{
}

void Transform::SetLocalScale(float size)
{
}

void Transform::SetLocalScale(float x, float y, float z)
{
}

void Transform::SetLocalScale(XMFLOAT3 scale)
{
}

void Transform::SetLocalScale(XMVECTOR scale)
{
}

void Transform::Translate(float x, float y, float z, Space space)
{
}

void Transform::Translate(XMFLOAT3 translation, Space space)
{
}

void Transform::Translate(XMVECTOR translation, Space space)
{
}

void Transform::Rotate(float x, float y, float z, Space space)
{
}

void Transform::Rotate(XMFLOAT4 rotation, Space space)
{
}

void Transform::Rotate(XMVECTOR rotation, Space space)
{
}

void Transform::SetParent(Transform* other)
{
}
