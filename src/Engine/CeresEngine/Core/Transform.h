#pragma once
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;
using namespace std;

enum Space
{
	SELF,
	PARENT,
	WORLD,
};

class Transform
{
private:

	XMVECTOR localPosition;
	XMVECTOR localRotation;
	XMVECTOR localScale;

	Transform* parent;
	size_t index;
	vector<Transform*> children;

public:
	Transform();
	Transform(float x, float y, float z);
	Transform(XMFLOAT3 position, XMFLOAT4 rotation, XMFLOAT3 scale);
	Transform(XMVECTOR position, XMVECTOR rotation, XMVECTOR scale);
	~Transform();

	XMVECTOR GetLocalPosition();
	XMVECTOR GetPosition();
	XMVECTOR GetLocalRotation();
	XMVECTOR GetRotation();
	XMVECTOR GetLocalScale();
	XMVECTOR GetScale();
	XMMATRIX GetWorldMatrix();
	XMVECTOR GetForwardVector();
	Transform* GetParent();
	Transform* GetChild(size_t index);
	size_t GetChildCount();

	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(XMFLOAT3 position);
	void SetLocalPosition(XMVECTOR position);
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 position);
	void SetPosition(XMVECTOR position);
	void SetLocalRotation(float x, float y, float z);
	void SetLocalRotation(XMFLOAT4 rotation);
	void SetLocalRotation(XMVECTOR rotation);
	void SetRotation(float x, float y, float z);
	void SetRotation(XMFLOAT4 rotation);
	void SetRotation(XMVECTOR rotation);
	void SetLocalScale(float size);
	void SetLocalScale(float x, float y, float z);
	void SetLocalScale(XMFLOAT3 scale);
	void SetLocalScale(XMVECTOR scale);

	void Translate(float x, float y, float z, Space space = Space::SELF);
	void Translate(XMFLOAT3 translation, Space space = Space::SELF);
	void Translate(XMVECTOR translation, Space space = Space::SELF);
	void Rotate(float x, float y, float z, Space space = Space::SELF);
	void Rotate(XMFLOAT4 rotation, Space space = Space::SELF);
	void Rotate(XMVECTOR rotation, Space space = Space::SELF);

protected:
	void SetParent(Transform* other);
};

