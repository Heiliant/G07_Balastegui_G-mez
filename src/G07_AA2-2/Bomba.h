#pragma once
#include "Casilla.h"
#include <time.h>
#include <stdlib.h>

class Bomba : public Casilla
{
public:
	Bomba();
	Bomba(std::pair<int, int> coord);
	~Bomba();

	void update() override;
	void draw() override;

	bool collideWithPlayer;
	bool isExploding;

private:
	float timeToExplode;
	float lastTime;

};

