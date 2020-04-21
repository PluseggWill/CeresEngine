#pragma once

#include "GameComponent.h"
#include "../Rendering/Camera.h"
#include <vector>
#include "..//Rendering/MeshData.h"

class Scene
{
	friend class GameComponent;
	friend class Camera;

protected:
	std::vector<GameComponent> GameComponentList;
	std::vector<Camera> CameraList;
	MeshData* SceneMeshData;
	
public:
	Scene();
	~Scene();
	bool AddToScene(Camera camera);
	bool AddToScene(GameComponent gameComponent);
	bool UpdateScene();
};

