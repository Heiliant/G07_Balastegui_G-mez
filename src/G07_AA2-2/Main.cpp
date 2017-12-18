#include <iostream>
#include "Scene.h"
#include "Renderer.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	Game* GameManager = new Game();

	GameManager->run();

	return 0; 
}