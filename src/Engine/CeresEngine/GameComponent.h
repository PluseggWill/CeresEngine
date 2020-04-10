#pragma once
class GameObject;

class GameComponent
{
	friend class GameObject;

private:
	bool isActive;

protected:
	GameObject* gameObject;

public:
	GameObject* GetGameObject();
	bool IsActive();
	void SetActive(bool flag);
};

