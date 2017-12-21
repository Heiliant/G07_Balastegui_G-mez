#include "Player.h"



Player::Player(int num) //añadir switch que gestione si se crea un player 1 o un player 2
{
	if (num == 1) {
		isPJ1 = true;

		photo.path = PATH_PJ1;
		photo.placeholder.x = 48;
		photo.placeholder.y = 48+80;

		whoIam = TIPO_CASILLA::PLAYER1;
	}
	else {
		isPJ1 = false;

		photo.path = PATH_PJ2;
		photo.placeholder.x = SCREEN_WIDTH-48*2;
		photo.placeholder.y = SCREEN_HEIGHT-48*2;

		photo.placeholder.x = 48*3;
		photo.placeholder.y = 48 + 80;

		whoIam = TIPO_CASILLA::PLAYER2;
	}

	photo.id=Renderer::Instance()->loadSpriteSheet(photo.path, 3, 4);

	vidas = 3;
	score = 0;

	lastTime = 0;
	counter = 0;

	
	canBomb = true;
	isInmune = false;
}


Player::~Player()
{
}

void Player::eventHandler()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (isPJ1) {
		if (keyboardState[SDL_SCANCODE_W])
			speed.second = -1;
		else if (keyboardState[SDL_SCANCODE_S])
			speed.second = 1;
		else if (keyboardState[SDL_SCANCODE_D])
			speed.first = 1;
		else if (keyboardState[SDL_SCANCODE_A])
			speed.first = -1;
		else {
			speed.first = 0;
			speed.second = 0;
		}
		if (keyboardState[SDL_SCANCODE_SPACE] && canBomb) {
			myBomb = new Bomba(getCenter());
			canBomb = false;
		}
	}
	else {
		if (keyboardState[SDL_SCANCODE_UP])
			speed.second = -1;
		else if (keyboardState[SDL_SCANCODE_DOWN])
			speed.second = 1;
		else if (keyboardState[SDL_SCANCODE_LEFT])
			speed.first = -1;
		else if (keyboardState[SDL_SCANCODE_RIGHT])
			speed.first = 1;
		else {
			speed.first = 0;
			speed.second = 0;
		}

		if (keyboardState[SDL_SCANCODE_RCTRL] && canBomb) {
			myBomb = new Bomba(getCenter());
			canBomb = false;
		}
	}
}

void Player::update()
{
	switch (speed.first) {
	case -1: spriteCoordinate.second = 1;
		break;
	case 0:
		break;
	case 1: spriteCoordinate.second = 3;
		break;
	}

	switch (speed.second) {
	case -1: spriteCoordinate.second = 0;
		break;
	case 0:
		break;
	case 1: spriteCoordinate.second = 2;
		break;
	}
	float deltaTime = clock() - lastTime;

	if (speed.first != 0 || speed.second != 0) {
		counter += deltaTime*0.005;
		if (counter >= 3)
			counter = 0;
		spriteCoordinate.first = static_cast<int>(counter);
	}
	else
		counter = 0;

	float speedInc = 1.0f;
	if (boots >= 0) {
		boots -= deltaTime;
		speedInc = 1.8f;
	}
	moveX(speed.first*speedInc);
	moveY(speed.second*speedInc);

	if (helmet >= 0) {
		helmet -= deltaTime;
		isInmune = true;
	}
	else
		isInmune = false;
	

	lastTime = clock();
}

void Player::draw()
{
	Renderer::Instance()->renderSprite(photo.id, photo.placeholder, spriteCoordinate);
}

void Player::moveX(float delta)
{
	float temp = delta;
	{
	if (delta != 1 && delta != 0)
		int l = 0;

	temp -= static_cast<int>(temp);
	delta -= temp;

	if (temp >= 0.5)
		temp = 1;
	else if (temp <= -0.5)
		temp = -1;
	else
		temp = 0;
	delta += temp;
	} //redondeamos delta, ya que si dejamos que el compilador lo castee, lo trunca y los positivos se vuelven 1 (siendo 1.8).
	photo.placeholder.x += delta;
}

void Player::moveY(float delta) 
{
	float temp = delta;
	{
		if (delta != 1 && delta != 0)
			int l = 0;

		temp -= static_cast<int>(temp);
		delta -= temp;

		if (temp >= 0.5)
			temp = 1;
		else if (temp <= -0.5)
			temp = -1;
		else
			temp = 0;
		delta += temp;
	} //redondeamos delta, ya que si dejamos que el compilador lo castee, lo trunca y los positivos se vuelven 1 (siendo 1.8).
	photo.placeholder.y += delta;
}

std::pair<int, int> Player::getPos() {
	return std::make_pair(photo.placeholder.x, photo.placeholder.y);
}

void Player::putHelmet()
{
	helmet = 10000;
}

void Player::putBoots()
{
	boots = 10000;
}


void Player::harm()
{
	vidas--;

	if (isPJ1) {
		photo.placeholder.x = 1 * 48;
		photo.placeholder.y = 1 * 48 + 80;
	}
	else {
		photo.placeholder.x = 13 * 48;
		photo.placeholder.y = 11 * 48 + 80;
	}
}




