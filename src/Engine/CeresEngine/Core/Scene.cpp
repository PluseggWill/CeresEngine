#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

bool Scene::AddToScene(Camera camera)
{
	CameraList.push_back(camera);
	return true;
}

bool Scene::AddToScene(GameComponent gameComponent)
{
	GameComponentList.push_back(gameComponent);
	return true;
}

bool Scene::UpdateScene()
{
	return true;
}