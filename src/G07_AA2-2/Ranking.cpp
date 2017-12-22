#include "Ranking.h"



Ranking::Ranking(std::vector<std::pair<std::string, int>> newComers)
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
	int j = 0;
	for (std::vector<std::pair<std::string, int>>::iterator i=newComers.begin(); i!=newComers.end() && j<10; ++i, ++j)
		beastList.push_back({ i->first, i->second, {} });//lee las puntuaciones de el argumento pasado por el game y los mete en la deque beastList

	//POR SI QUIERES PROBAR COMO VA, ESTO INSERTA UNOS CUANTOS VALORES

	/*beastList.push_back({ "kek", 123, {} });
	beastList.push_back({ "lol", 321,{} });
	beastList.push_back({ "lmao", 54,{} });
	beastList.push_back({ "boi", 456,{} });
	beastList.push_back({ "dat", 73,{} });
	beastList.push_back({ "dejavu", 28,{} });
	beastList.push_back({ "spice", 853,{} });*/


	std::sort(beastList.begin(), beastList.end()); //lo ordena de menor a mayor
	std::reverse(beastList.begin(), beastList.end()); //le da la vuelta

	j = 0;
	for (std::deque<Score>::iterator i = beastList.begin(); i != beastList.end(); ++i, ++j) {//da valor a los atributos de imágen de las puntuaciones
		i->face.path = PATH_GAMEOVER;
		i->face.placeHolder.h = 50;
		i->face.placeHolder.w = 200;
		i->face.placeHolder.x = SCREEN_WIDTH / 2 - i->face.placeHolder.w/2;
		i->face.placeHolder.y = SCREEN_HEIGHT * j / 10;
		i->face.size = 200;
		i->face.color = { 0, 1, 0, 1 };
		i->face.msg = std::string(i->name + " " + std::to_string(i->points));
		i->face.id=Renderer::Instance()->loadText(i->face);
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
	for(std::deque<Score>::reverse_iterator i = beastList.rbegin(); i != beastList.rend(); ++i) {
		Renderer::Instance()->renderIMG(i->face.id, i->face.placeHolder);
	}
}

