#pragma once
#include "Scene.h"
#include "Scene.h"
#include "Button.h"
#include "Renderer.h"

class Menu : public Scene
{
public:
	Menu();
	~Menu();

	
private:
	Text titulo;
	Image BG;

	void eventHandler() override;
	void update() override;
	void draw() override;

	Button* playOne;
	Button* playTwo;
	Button* exit;
	Button* ranking;
	Button* switchSound;

	Mix_Music* bgm;

};

