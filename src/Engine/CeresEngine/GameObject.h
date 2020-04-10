#pragma once

#include "GameComponent.h"
#include "Transform.h"

#include <typeindex>
#include <unordered_map>
#include <string>

using namespace std;

class GameObject
{
private:
	string name;
	unordered_map<type_index, GameComponent*> components;
	bool isActive;
	bool isStatic;
	bool isDestroyed;

public:
	Transform transform;

	GameObject();
	GameObject(float x, float y, float z);
	GameObject(XMVECTOR position, XMVECTOR rotation, XMVECTOR scale);
	~GameObject();

	string GetName();
	GameObject* GetParent();
	GameObject* GetChild(size_t index);
	template<class T> T* GetComponent();
	bool IsActive();
	bool IsStatic(); 

	void SetName(string name);
	void SetParent(GameObject* other);
	template<class T, class... argTs> T* AddComponent(argTs... args);
	template<class T> void RemoveComponent();
};

