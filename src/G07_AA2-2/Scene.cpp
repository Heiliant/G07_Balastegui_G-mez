#include "Scene.h"

Scene::Scene()
{
	active = true;
	CurrentGameState = GAME_STATE::STAY;
}


Scene::~Scene()
{
}

void Scene::eventHandler()
{
}

void Scene::update()
{
}

void Scene::draw()
{
}

bool Scene::isRunning() { return active; }