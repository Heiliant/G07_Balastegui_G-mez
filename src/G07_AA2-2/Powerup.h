#pragma once
#include "Casilla.h"
class Powerup :
	public Casilla
{
public:
	Powerup();
	~Powerup();

	void draw() override;

	bool isHelmet;
};

