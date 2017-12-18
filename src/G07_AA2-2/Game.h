#pragma once
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"
#include "Renderer.h"

class Game
{
public:
	Game();
	~Game();

	Scene* currentScene;
	bool running;

	void run();
	void updateScene();
};

