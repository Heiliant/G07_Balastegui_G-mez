#pragma once
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"
#include "Renderer.h"
#include <vector>

class Game
{
public:
	Game();
	~Game();

	Scene* currentScene;
	bool running;

	std::string nameToAdd;
	int scoreToAdd;

	void run();
	void updateScene();

	std::vector<std::pair<std::string, int>> toAddList;
};

