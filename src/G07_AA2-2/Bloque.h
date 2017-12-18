#pragma once
#include "Casilla.h"

class Bloque : public Casilla
{
public:
	Bloque();
	~Bloque();

	void draw() override;
	void update() override;
};

