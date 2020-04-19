#pragma once

#include "GameComponent.h"
#include "../Rendering/Camera.h"

class Scene
{
	friend class GameComponent;
	friend class Camera;

protected:
	GameComponent* mGameComponent;
	Camera* mCamera;
	
public:
	Scene();
	~Scene();

};

