#include "HUD.h"



HUD::HUD(std::pair<Player*, Player*> users) : m_users{ users }
{
	score.first = m_users.first->score;
	score.second = m_users.second->score;

	vidas.first = m_users.first->vidas;
	vidas.second = m_users.second->vidas;

	timer = PLAYTIME;

	displayTime.path = PATH_GAMEOVER;
	displayTime.size = 200;
	displayTime.color = { 0, 0, 0, 255 };
	displayTime.msg = "0";
	displayTime.placeHolder.w = 100;
	displayTime.placeHolder.h = 100;
	displayTime.placeHolder.x = SCREEN_WIDTH/2 - displayTime.placeHolder.w/2;
	displayTime.placeHolder.y = -20;
	displayTime.id = Renderer::Instance()->loadText(displayTime);

	lastTime = clock();

	//SCORE
	displayScore.first.path = PATH_GAMEOVER;
	displayScore.first.size = 200;
	displayScore.first.color={ 0, 0, 0, 255 };
	displayScore.first.msg = "0";
	displayScore.first.placeHolder.w = 60;
	displayScore.first.placeHolder.h = 40;
	displayScore.first.placeHolder.x = HUD_X_MARGIN;
	displayScore.first.placeHolder.y = 0;
	displayScore.first.id = Renderer::Instance()->loadText(displayScore.first);

	displayScore.second.path = PATH_GAMEOVER;
	displayScore.second.size = 200;
	displayScore.second.color = { 0, 0, 0, 255 };
	displayScore.second.msg = "0";
	displayScore.second.placeHolder.w = 60;
	displayScore.second.placeHolder.h = 40;
	displayScore.second.placeHolder.x = SCREEN_WIDTH - HUD_X_MARGIN - displayScore.second.placeHolder.w;
	displayScore.second.placeHolder.y = 0;
	displayScore.second.id = Renderer::Instance()->loadText(displayScore.second);


	//VIDAS
	displayVidas.first.path = PATH_GAMEOVER;
	displayVidas.first.size = 200;
	displayVidas.first.color = { 0, 0, 0, 255 };
	displayVidas.first.msg = "0";
	displayVidas.first.placeHolder.w = 60;
	displayVidas.first.placeHolder.h = 40;
	displayVidas.first.placeHolder.x = HUD_X_MARGIN;
	displayVidas.first.placeHolder.y = 40;
	displayVidas.first.id = Renderer::Instance()->loadText(displayVidas.first);

	displayVidas.second.path = PATH_GAMEOVER;
	displayVidas.second.size = 200;
	displayVidas.second.color = { 0, 0, 0, 255 };
	displayVidas.second.msg = "0";
	displayVidas.second.placeHolder.w = 60;
	displayVidas.second.placeHolder.h = 40;
	displayVidas.second.placeHolder.x = SCREEN_WIDTH - HUD_X_MARGIN - displayVidas.second.placeHolder.w;
	displayVidas.second.placeHolder.y = 40;
	displayVidas.second.id = Renderer::Instance()->loadText(displayVidas.second);
}


HUD::~HUD()
{
}

void HUD::update() {
	float deltaTime = clock() - lastTime;

	displayScore.first.msg = "Score: " + std::to_string(m_users.first->score);
	Renderer::Instance()->loadText(displayScore.first, displayScore.first.id);
	displayScore.second.msg = "Score: " + std::to_string(m_users.second->score);
	Renderer::Instance()->loadText(displayScore.second, displayScore.second.id);

	displayVidas.first.msg = "Vidas: " + std::to_string(m_users.first->vidas);
	Renderer::Instance()->loadText(displayVidas.first, displayVidas.first.id);
	displayVidas.second.msg = "Vidas: " + std::to_string(m_users.second->vidas);
	Renderer::Instance()->loadText(displayVidas.second, displayVidas.second.id);

	timer -= deltaTime;
	displayTime.msg = std::to_string(static_cast<int>(timer/1000));
	Renderer::Instance()->loadText(displayTime, displayTime.id);

	lastTime = clock();
}

void HUD::draw() {
	Renderer::Instance()->renderIMG(displayScore.first.id, displayScore.first.placeHolder);
	Renderer::Instance()->renderIMG(displayScore.second.id, displayScore.second.placeHolder);

	Renderer::Instance()->renderIMG(displayVidas.first.id, displayVidas.first.placeHolder);
	Renderer::Instance()->renderIMG(displayVidas.second.id, displayVidas.second.placeHolder);

	Renderer::Instance()->renderIMG(displayTime.id, displayTime.placeHolder);
}