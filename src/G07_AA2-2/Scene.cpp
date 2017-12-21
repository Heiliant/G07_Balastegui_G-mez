#include "Scene.h"

Scene::Scene()
{
	active = true;
	CurrentGameState = GAME_STATE::STAY;

	winnerN = "notaname";
	winnerS = -1;
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