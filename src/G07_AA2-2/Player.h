#pragma once
#include "Casilla.h"
#include "Renderer.h"
#include "Bomba.h"
#include <time.h>
#include <stdlib.h>

class Player : public Casilla
{
public:
	Player() {};
	Player(int num);
	~Player();

	void eventHandler();
	void update() override;
	void draw() override;
	void harm() override;
	
	void moveX(float delta);
	void moveY(float delta);
	std::pair<int, int> getPos();
	std::pair<int, int> getSpeed() { return speed; }

	void putHelmet();
	void putBoots();


private:
	

public:
	int vidas;
	int score;
	bool canBomb;
	Bomba* myBomb;

	bool isInmune;

private:
	std::pair<int, int> speed;
	bool isPJ1;
	std::pair<int, int> spriteCoordinate;
	float lastTime;
	float counter;
	int local;

	float helmet;
	float boots;
};

