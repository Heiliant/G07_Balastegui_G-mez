#pragma once
#include "Recursos.h"
#include "Renderer.h"
#include <iostream>
#include <SDL_ttf.h>

class Button
{
public:
	Button();
	~Button();

	bool isClicked();
	bool isHovered();
	void eventHandler(SDL_Event evnt);
	void update();
	void draw();

	void resetText(Text newcomer);

private:
	Text message;
	bool leftClick;
};

