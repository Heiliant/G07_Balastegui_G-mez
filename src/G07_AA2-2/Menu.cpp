#include "Menu.h"

Menu::Menu()
{
	BG.path = PATH_BG;
	BG.placeholder.x = 0;
	BG.placeholder.y = 0;
	BG.placeholder.w = SCREEN_WIDTH;
	BG.placeholder.h = SCREEN_HEIGHT;

	BG.id=Renderer::Instance()->loadIMG(BG.path);

	playOne = new Button();                                            
	Text reset;
	reset.path = PATH_SAIYAN;
	reset.placeHolder.w = 200;
	reset.placeHolder.h = 100;
	reset.placeHolder.x = SCREEN_WIDTH/2- reset.placeHolder.w/2;
	reset.placeHolder.y = SCREEN_HEIGHT*0.2;
	reset.size = 200;
	reset.color = { 0,255,0,255 };
	reset.msg = "PLAY ONE";

	playOne->resetText(reset);

	playTwo = new Button(); 
	reset.placeHolder.w = 200;
	reset.placeHolder.h = 100;
	reset.placeHolder.x = SCREEN_WIDTH / 2 - reset.placeHolder.w / 2;
	reset.placeHolder.y = SCREEN_HEIGHT*0.4;
	reset.size = 200;
	reset.color = { 0,255,0,255 };
	reset.msg = "PLAY TWO";

	playTwo->resetText(reset);

	ranking = new Button();
	reset.placeHolder.w = 200;
	reset.placeHolder.h = 100;
	reset.placeHolder.x = SCREEN_WIDTH / 2 - reset.placeHolder.w / 2;
	reset.placeHolder.y = SCREEN_HEIGHT*0.6;
	reset.size = 200;
	reset.color = { 0,0,255,255 };
	reset.msg = "RANKING";

	ranking->resetText(reset);

	exit = new Button();
	reset.placeHolder.w = 200;
	reset.placeHolder.h = 100;
	reset.placeHolder.x = SCREEN_WIDTH / 2 - reset.placeHolder.w / 2;
	reset.placeHolder.y = SCREEN_HEIGHT*0.8;
	reset.size = 200;
	reset.color = { 255,0,0,255 };
	reset.msg = "EXIT";

	exit->resetText(reset);

	switchSound = new Button();
	reset.placeHolder.w = 100;
	reset.placeHolder.h = 80;
	reset.placeHolder.x = SCREEN_WIDTH - reset.placeHolder.w*1.5;
	reset.placeHolder.y = SCREEN_HEIGHT - reset.placeHolder.h*1.4;
	reset.size = 200;
	reset.color = { 255,0,255,255 };
	reset.msg = "MUTE";

	switchSound->resetText(reset);


	bgm = Mix_LoadMUS("../../res/au/menu.mp3");
	Mix_PlayMusic(bgm, -1);
}


Menu::~Menu()
{
	Mix_FreeMusic(bgm);
	bgm = nullptr;
}

void Menu::eventHandler()
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

		if (playOne->isClicked())
		{
			CurrentGameState = GAME_STATE::PLAY1;
		}
		if (playTwo->isClicked())
		{
			CurrentGameState = GAME_STATE::PLAY2;
		}
		if (ranking->isClicked())
		{
			CurrentGameState = GAME_STATE::RANKING;
		}
		if (exit->isClicked())
		{
			active = false;
		}
		if (switchSound->isClicked()) {
			if (Mix_PlayingMusic()) {
				Mix_HaltMusic();
			}
			else {
				Mix_PlayMusic(bgm, -1);
			}
		}

		playOne->eventHandler(evnt);
		playTwo->eventHandler(evnt);
		ranking->eventHandler(evnt);
		exit->eventHandler(evnt);
		switchSound->eventHandler(evnt);
	}
}

void Menu::update()
{
	playOne->update();
	playTwo->update();
	ranking->update();
	exit->update();
	switchSound->update();
}

void Menu::draw()
{
	Renderer::Instance()->renderIMG(BG.id, BG.placeholder);

	playOne->draw();
	playTwo->draw();
	ranking->draw();
	exit->draw();
	switchSound->draw();
}
