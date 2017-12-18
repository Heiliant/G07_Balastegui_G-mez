#include "Muro.h"



Muro::Muro()
{
	whoIam = TIPO_CASILLA::MURO;
}


Muro::~Muro()
{
}

void Muro::draw() {
	Renderer::Instance()->renderSprite(photo.id, photo.placeholder, std::make_pair(1, 0));
}

void Muro::update() {

}