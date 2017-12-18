#include "Ranking.h"



Ranking::Ranking()
{
	Back = new Button();
	//Back->message.placeHolder.x = 650;
	//Back->message.placeHolder.y = 350;
	//Back->message.placeHolder.w = 100; //por probar
	//Back->message.placeHolder.h = 50;
	//Back->message.size = 20;
	//Back->message.color = { 0,0,0,1 };
	//Back->message.msg = "BACK";
}


Ranking::~Ranking()
{
}

void Ranking::eventHandler()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			active = false;
			break;
		case SDL_WINDOWEVENT_MOVED:
			break;
		}

	}

	Back->eventHandler(evnt);
	if (Back->isClicked()) //aqui el estado vuelve a ser menu, para que se vuelva a hacer un new menu, pero me cagu en la mare del tanu porque hace lo que quiere el game.cpp
	{
		CurrentGameState = GAME_STATE::MENU;
	}
}

void Ranking::update()
{
	Back->update();
}

void Ranking::draw()
{
}
