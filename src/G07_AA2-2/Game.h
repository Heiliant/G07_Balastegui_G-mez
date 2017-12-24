#pragma once
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"
#include "Renderer.h"
#include <fstream>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	Scene* currentScene;
	bool running;
	std::string hola = "gaga";
	int o = 2;

	std::string nameToAdd;
	int scoreToAdd;

	void run();
	void updateScene();

	void LeerBinario();
	void EscribirBinario();
	std::vector<std::pair<std::string, int>> toAddList;

};

