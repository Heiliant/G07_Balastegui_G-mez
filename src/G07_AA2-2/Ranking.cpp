#include "Ranking.h"



Ranking::Ranking()
{
	BG.path = PATH_BG;
	BG.placeholder.x = 0;
	BG.placeholder.y = 0;
	BG.placeholder.w = SCREEN_WIDTH;
	BG.placeholder.h = SCREEN_HEIGHT;

	BG.id = Renderer::Instance()->loadIMG(BG.path);

	Back = new Button();
	Text reset;

	reset.color = { 0,0,0,1 };;
	reset.msg="BACK";
	reset.path=PATH_SAIYAN;
	reset.placeHolder.x=SCREEN_WIDTH*0.775f;
	reset.placeHolder.y=SCREEN_HEIGHT*0.85f;
	reset.placeHolder.h = 50;
	reset.placeHolder.w = 100;
	reset.size=200;

	Back->resetText(reset);

	for (int i = 0; i < 10; ++i)
	beastList.push_back({ "Alex", rand()%1000, {} });

	int j = 0;
	for (std::deque<Score>::iterator i = beastList.begin(); i != beastList.end(); ++i) {
		i->face.path = PATH_GAMEOVER;
		i->face.placeHolder.h = 50;
		i->face.placeHolder.w = 200;
		i->face.placeHolder.x = SCREEN_WIDTH / 2 - i->face.placeHolder.w/2;
		i->face.placeHolder.y = SCREEN_HEIGHT * j / 10;
		i->face.size = 200;
		i->face.color = { 0, 1, 0, 1 };
		i->face.msg = std::string(i->name + " " + std::to_string(i->points));
		i->face.id=Renderer::Instance()->loadText(i->face);
		j++;
	}
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
	Renderer::Instance()->renderIMG(BG.id, BG.placeholder);
	Back->draw();
	displayScores();
}

void Ranking::displayScores()
{
	for(std::deque<Score>::iterator i = beastList.begin(); i != beastList.end(); ++i) {
		Renderer::Instance()->renderIMG(i->face.id, i->face.placeHolder);
	}
}

