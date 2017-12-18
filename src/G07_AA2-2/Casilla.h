#pragma once
#include <deque>
#include <SDL.h>
#include "Recursos.h"
#include "Renderer.h"

class Casilla
{
public:
	Casilla();
	~Casilla();

	std::pair<int, int> getCenter();
	bool doCollide(Casilla other);
	void correctPosition(Casilla* other);

	virtual void harm();
	virtual void update();
	virtual void draw();

	bool killMe;

	Image photo;
	
	TIPO_CASILLA whoIam;

	std::pair<int, int> spriteCoord;
};

