#include "Bomba.h"



Bomba::Bomba()
{
}

Bomba::Bomba(std::pair<int, int> coord) 
{
	
	photo.placeholder.x = coord.first - 48 / 2;
	photo.placeholder.y = coord.second - 48 / 2;

	collideWithPlayer = false;

	timeToExplode = 5000;
	lastTime = clock();
	isExploding = false;
}


Bomba::~Bomba()
{
	
}

void Bomba::update()
{
	float deltaTime = clock() - lastTime;
	timeToExplode -= deltaTime;
	if (timeToExplode <= 0) {
		isExploding = true;
	}

	lastTime = clock();
}

void Bomba::draw()
{
	Renderer::Instance()->renderSprite(photo.id, photo.placeholder, std::make_pair(0, 1));
}
