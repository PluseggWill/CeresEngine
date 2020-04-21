#include "Camera.h"

# define M_PI           3.14159265358979323846  /* pi */

Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f, 0.0f),
	  mRight(1.0f, 0.0f, 0.0f, 0.0f),
	  mUp(0.0f, 1.0f, 0.0f, 0.0f),
	  mLook(0.0f, 0.0f, 1.0f, 0.0f)
{
	SetLens(0.25f * M_PI, 1.0f, 1.0f, 1000.0f);
	UpdateViewMatrix();
}

Camera::~Camera()
{

}

XMVECTOR Camera::GetPositionXM() const
{
	return XMLoadFloat4(&mPosition);
}

XMFLOAT4 Camera::GetPosition() const
{
	return mPosition;
}

void Camera::SetPosition(float x, float y, float z)
{
	FXMVECTOR V = XMVectorSet(x, y, z, 0.0f);
	XMStoreFloat4(&mPosition, V);
	UpdateViewMatrix();
}

void Camera::SetPosition(const XMFLOAT4& v)
{
	// To do
	XMVECTOR V;
	XMStoreFloat4(&mPosition, V);
}

// Get camera basis vectors.
XMVECTOR Camera::GetRightXM() const
{
	return XMLoadFloat4(&mRight);
}

XMFLOAT4 Camera::GetRight() const
{
	return mRight;
}

XMVECTOR Camera::GetUpXM() const
{
	return XMLoadFloat4(&mUp);
}

XMFLOAT4 Camera::GetUp() const
{
	return mUp;
}

XMVECTOR Camera::GetLookXM() const
{
	return XMLoadFloat4(&mLook);
}

XMFLOAT4 Camera::GetLook() const
{
	return mLook;
}

void Camera::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	mFovY = fovY;
	mAspect = aspect;

	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);

	XMStoreFloat4x4(&mProj, P);
}

float Camera::GetNearZ()const
{
	return mNearZ;
}

float Camera::GetFarZ()const
{
	return mFarZ;
}

float Camera::GetAspect()const
{
	return mAspect;
}

float Camera::GetFovY()const
{
	return mFovY;
}

float Camera::GetFovX()const
{
	float halfWidth = 0.5f * GetFarWindowWidth();
	return 2.0f * atan(halfWidth / mNearZ);
}

XMMATRIX Camera::View()const
{
	return XMLoadFloat4x4(&mView);
}

XMMATRIX Camera::Proj()const
{
	return XMLoadFloat4x4(&mProj);
}

XMMATRIX Camera::ViewProj()const
{
	return XMMatrixMultiply(View(), Proj());
}

float Camera::GetNearWindowWidth()const
{
	return mAspect * mNearWindowHeight;
}

float Camera::GetNearWindowHeight()const
{
	return mNearWindowHeight;
}

float Camera::GetFarWindowWidth()const
{
	return mAspect * mFarWindowHeight;
}

float Camera::GetFarWindowHeight()const
{
	return mFarWindowHeight;
}

void Camera::Strafe(float d)
{
	// mPosition += d*mRight
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat4(&mRight);
	XMVECTOR p = XMLoadFloat4(&mPosition);
	XMStoreFloat4(&mPosition, XMVectorMultiplyAdd(s, r, p));
	UpdateViewMatrix();
}

void Camera::Walk(float d)
{
	// mPosition += d*mLook
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat4(&mLook);
	XMVECTOR p = XMLoadFloat4(&mPosition);
	XMStoreFloat4(&mPosition, XMVectorMultiplyAdd(s, l, p));
	UpdateViewMatrix();
}

void Camera::LookAt(FXMVECTOR pos, FXMVECTOR dir, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(dir, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat4(&mPosition, pos);
	XMStoreFloat4(&mLook, L);
	XMStoreFloat4(&mRight, R);
	XMStoreFloat4(&mUp, U);
	UpdateViewMatrix();
}

void Camera::LookAt(const XMFLOAT4& pos, const XMFLOAT4& dir, const XMFLOAT4& up)
{
	XMVECTOR P = XMLoadFloat4(&pos);
	XMVECTOR D = XMLoadFloat4(&dir);
	XMVECTOR U = XMLoadFloat4(&up);

	LookAt(P, D, U);
}

void Camera::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat4(&mRight), angle);

	XMStoreFloat4(&mUp, XMVector3TransformNormal(XMLoadFloat4(&mUp), R));
	XMStoreFloat4(&mLook, XMVector3TransformNormal(XMLoadFloat4(&mLook), R));
	UpdateViewMatrix();
}

void Camera::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.
	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat4(&mRight, XMVector3TransformNormal(XMLoadFloat4(&mRight), R));
	XMStoreFloat4(&mUp, XMVector3TransformNormal(XMLoadFloat4(&mUp), R));
	XMStoreFloat4(&mLook, XMVector3TransformNormal(XMLoadFloat4(&mLook), R));
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR R = XMLoadFloat4(&mRight);
	XMVECTOR U = XMLoadFloat4(&mUp);
	XMVECTOR L = XMLoadFloat4(&mLook);
	XMVECTOR P = XMLoadFloat4(&mPosition);

	XMMATRIX V = XMMatrixLookToLH(
		P,
		L,
		U);

	XMStoreFloat4x4(&mView, V);
}