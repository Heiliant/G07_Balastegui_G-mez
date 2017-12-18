#include "Explosion.h"



Explosion::Explosion()
{
	photo.path = PATH_EXPLOSION;
	photo.id = Renderer::Instance()->loadSpriteSheet(photo.path, 4, 7);
	
	lastTime = clock();
	lifeSpan = 1500;

	spriteCoord.first = 0;
	spriteCoord.second = -1;

	whoIam = TIPO_CASILLA::EXPLOSION;
}


Explosion::~Explosion()
{
}

void Explosion::draw()
{
	if(spriteCoord.second!=-1)
	Renderer::Instance()->renderSprite(photo.id, photo.placeholder, spriteCoord);
}

void Explosion::update()
{
	float deltaTime = clock() - lastTime;

	lifeSpan -= deltaTime;

	if (lifeSpan <= 0)
		killMe = true;
	else if (lifeSpan <= 1500 / 4)
		spriteCoord.first = 0;
	else if(lifeSpan<=1500/2)
		spriteCoord.first = 1;
	else if(lifeSpan<=(1500*3/4))
		spriteCoord.first = 2;
	else
		spriteCoord.first = 3;
	lastTime = clock();
}

