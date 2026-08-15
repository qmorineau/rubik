#include "Scene.hpp"
#include "Window.hpp"

Scene::Scene() :
	_camera(SCR_WIDTH, SCR_HEIGHT)
{}

Scene::~Scene() {}

void Scene::update(float deltaTime)
{
	_cube.update(deltaTime);
};