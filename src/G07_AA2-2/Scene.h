#pragma once
#include "Button.h"
#include <SDL.h>
#include <deque>

#include <iostream>

class Scene
{
public:
	Scene();
	~Scene();

	virtual void eventHandler();
	virtual void update();
	virtual void draw();

	bool isRunning();
	GAME_STATE CurrentGameState;

protected:
	SDL_Texture* BG;
	std::deque <Button> buttonList;
	bool active;
	
	
};

