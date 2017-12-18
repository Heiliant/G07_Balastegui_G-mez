#pragma once
#include "Casilla.h"
class Muro : public Casilla
{
public:
	Muro();
	~Muro();

	void draw() override;
	void update() override;
};

