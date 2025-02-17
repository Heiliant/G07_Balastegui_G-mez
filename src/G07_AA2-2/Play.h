#pragma once
#include "HUD.h"
#include "Scene.h"
#include "Casilla.h"
#include "Player.h"
#include "Bomba.h"
#include "Muro.h"
#include "Bloque.h"
#include "Explosion.h"
#include "Powerup.h"
#include <deque>
#include <set>
#include "Button.h"
#include "Renderer.h"
#include <string>
#include <sstream>
#include <rapidxml_print.hpp>
#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_utils.hpp>
#include <cstdlib>


class Play : public Scene
{
public:
	Play(int i);
	~Play();

private:

	Image bg;
	HUD *interfaz;
	std::pair <Player*, Player*> users;
	std::pair <Bomba*, Bomba*> bombList;
	std::deque<Powerup*> powerupList;
	Casilla*** board;

	void eventHandler() override;
	void update() override;
	void draw() override;
	void LeerXml();

	float auxTime;
	int KnowLevel;
	
	Mix_Music* bgm;


};

