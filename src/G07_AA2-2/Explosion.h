#pragma once
#include "Casilla.h"
#include <time.h>
#include <stdlib.h>

class Explosion :
	public Casilla
{
public:
	Explosion();
	~Explosion();

	void draw() override;
	void update() override;

	

private:
	float lastTime;
	float lifeSpan;
};

