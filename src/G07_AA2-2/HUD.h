#pragma once
#include "Player.h"


class HUD
{
public:
	HUD(std::pair<Player*, Player*> users);
	~HUD();
private:
	float countDown;
	std::pair <int, int> vidas;
	std::pair <int, int> score;
	std::pair<Player*, Player*> m_users;

	std::pair <Text, Text> displayScore;
	std::pair <Text, Text> displayVidas;

	
	float lastTime;
	Text displayTime;

public:
	void update();
	void draw();

	float timer;
};

