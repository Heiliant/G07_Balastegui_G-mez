#include "Powerup.h"



Powerup::Powerup()
{
	isHelmet = rand() % 2;
}


Powerup::~Powerup()
{
}

void Powerup::draw()
{

	Renderer::Instance()->renderSprite(photo.id, photo.placeholder, std::make_pair(1+isHelmet, 1));
}
