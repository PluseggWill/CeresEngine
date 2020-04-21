#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Camera
{
public:
	Camera();
	~Camera();

	// Get/Set world camera position.
	XMVECTOR GetPositionXM() const;
	XMFLOAT4 GetPosition() const;
	void SetPosition(float x, float y, float z);
	void SetPosition(const XMFLOAT4& v);

	// Get camera basis vectors.
	XMVECTOR GetRightXM() const;
	XMFLOAT4 GetRight() const;
	XMVECTOR GetUpXM() const;
	XMFLOAT4 GetUp() const;
	XMVECTOR GetLookXM() const;
	XMFLOAT4 GetLook() const;

	// Get frustum properties.
	float GetNearZ() const;
	float GetFarZ() const;
	float GetAspect() const;
	float GetFovY() const;
	float GetFovX() const;

	// Get near and far plane dimensions in view space coordinates
	float GetNearWindowWidth() const;
	float GetNearWindowHeight() const;
	float GetFarWindowWidth() const;
	float GetFarWindowHeight() const;

	// Set frustum.
	void SetLens(float fovY, float aspect, float zn, float zf);

	// Define Camera space via LookAt parameters.
	void LookAt(FXMVECTOR pos, FXMVECTOR dir, FXMVECTOR worldUp);
	void LookAt(const XMFLOAT4& pos, const XMFLOAT4& dir, const XMFLOAT4& up);

	// Get View/Proj matrices.
	XMMATRIX View() const;
	XMMATRIX Proj() const;
	XMMATRIX ViewProj() const;

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);
	void Walk(float d);

	// Rotate the camera.
	void Pitch(float angle);
	void RotateY(float angle);

	// After modifying camera position/orientation
	// call to rebuild the view matrix once per frame.
	void UpdateViewMatrix();

private:
	XMFLOAT4 mPosition; // view space origin
	XMFLOAT4 mRight; // view space x-axis
	XMFLOAT4 mUp; // view space y-axis
	XMFLOAT4 mLook; // view space z-axis

	// Cache frustum properties.
	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	// Cache View/Proj matrices.
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};

