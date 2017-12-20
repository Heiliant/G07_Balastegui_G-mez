#include "Play.h"



Play::Play(int i)
{
	bg.placeholder.x = 0;
	bg.placeholder.y = 0;
	bg.placeholder.w = SCREEN_WIDTH;
	bg.placeholder.h = SCREEN_HEIGHT;
	bg.path = PATH_BG;

	users.first = new Player(1);
	users.second = new Player(2);

	interfaz = new HUD(users);

	board = new Casilla**[15];
	for (int i = 0; i < 15; ++i) {
		board[i] = new Casilla*[13];
	}
	LeerXml();


	if (i == 1) {
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 13; ++j) {
				if (i == 0 || i == 14 || j == 0 || j == 12) {
					board[i][j] = new Bloque();
					board[i][j]->photo.placeholder.x = i * 48;
					board[i][j]->photo.placeholder.y = j * 48 + 80;
				}
				else if ((j == 2 || j == 4 || j == 6 || j == 8 || j == 10) && (i == 2 || i == 4 || i == 6 || i == 8 || i == 10 || i == 12)) {
					board[i][j] = new Bloque();
					board[i][j]->photo.placeholder.x = i * 48;
					board[i][j]->photo.placeholder.y = j * 48 + 80;
				}
				else {
					board[i][j] = nullptr;
				}

			}
		}
	}
	else {
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 13; ++j) {
				if (i == 0 || i == 14 || j == 0 || j == 12) {
					board[i][j] = new Bloque();
					board[i][j]->photo.placeholder.x = i * 48;
					board[i][j]->photo.placeholder.y = j * 48 + 80;
				}
				else if (((i>=6)&&(i<=8 ))|| ((j>=5) && (j<=7))) {
					board[i][j] = new Muro();
					board[i][j]->photo.placeholder.x = i * 48;
					board[i][j]->photo.placeholder.y = j * 48 + 80;
				}
				else {
					board[i][j] = nullptr;
				}

			}
		}
	}
	auxTime = 256;

	bgm = Mix_LoadMUS("../../res/au/game_theme.mp3");
	Mix_PlayMusic(bgm, -1);
	
}


Play::~Play()
{
	Mix_FreeMusic(bgm);
	bgm = nullptr;
}

void Play::eventHandler()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			active = false;
			break;
		case SDL_WINDOWEVENT_MOVED:
			break;
		}
		users.first->eventHandler();
		users.second->eventHandler();
	}
}

void Play::update()
{
	interfaz->update();
	users.first->update();
	users.second->update();

	//ACTUALIZAR BOARD CON LOS PUNTEROS A LOS PLAYERS
	board[users.first->getCenter().first / 48][(users.first->getCenter().second - 80) / 48] = users.first;
	board[users.second->getCenter().first / 48][(users.second->getCenter().second - 80) / 48] = users.second;

	//COLISIONES ENTRE PLAYERS
	if(users.first->getSpeed().first!=0 || users.first->getSpeed().second != 0) //tremen cacao vamos a tener para comprobar todas las colisiones
		users.first->correctPosition(users.second);
	if (users.second->getSpeed().first != 0 || users.second->getSpeed().second != 0)
		users.second->correctPosition(users.first);
	
	//COLISIONES ENTRE PLAYER Y ESCENARIO
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 13; ++j) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->whoIam!=TIPO_CASILLA::PLAYER2 && board[i][j]->whoIam != TIPO_CASILLA::PLAYER1) {
					users.first->correctPosition(board[i][j]);
					users.second->correctPosition(board[i][j]);
				}
				board[i][j]->update();
				if (board[i][j]->whoIam == TIPO_CASILLA::EXPLOSION && board[i][j]->spriteCoord.second == -1) {
					bool arr, abj, izq, der;
					arr = abj = izq = der = false;
					if (board[i + 1][j] != nullptr) {
						if (board[i + 1][j]->whoIam == TIPO_CASILLA::EXPLOSION)
							der = true;
					}
					if (board[i - 1][j] != nullptr) {
						if (board[i - 1][j]->whoIam == TIPO_CASILLA::EXPLOSION)
							izq = true;
					}
					if (board[i][j + 1] != nullptr) {
						if (board[i][j + 1]->whoIam == TIPO_CASILLA::EXPLOSION)
							arr = true;
					}
					if (board[i][j - 1] != nullptr) {
						if (board[i][j - 1]->whoIam == TIPO_CASILLA::EXPLOSION)
							abj = true;
					}

					if (!arr && !abj && !izq && der)//der
						board[i][j]->spriteCoord.second = 1;
					else if (!arr && !abj && izq && !der)//izq
						board[i][j]->spriteCoord.second = 2;
					else if (arr && !abj && !izq && !der)//arr
						board[i][j]->spriteCoord.second = 3;
					else if (!arr && abj && !izq && !der)//abj
						board[i][j]->spriteCoord.second = 4;
					else if (!arr && !abj && izq && der)//horizontal
						board[i][j]->spriteCoord.second = 5;
					else if (arr && abj && !izq && !der)//vertical
						board[i][j]->spriteCoord.second = 6;
					else//todas
						board[i][j]->spriteCoord.second = 0;
				}
				if (((users.first->getCenter().first/48 != i) || ((users.first->getCenter().second-80)/48)!=j) && (board[i][j]->whoIam==TIPO_CASILLA::PLAYER1)) {
					board[i][j] = nullptr; //CUANDO EL PLAYER SALE DE UNA CASILLA, ESTA DEJA DE APUNTAR A ÉL
				}
				else if (((users.second->getCenter().first / 48 != i) || ((users.second->getCenter().second - 80) / 48) != j) && (board[i][j]->whoIam == TIPO_CASILLA::PLAYER2)) {
					board[i][j] = nullptr; //CUANDO EL PLAYER SALE DE UNA CASILLA, ESTA DEJA DE APUNTAR A ÉL
				}
				if (board[i][j]!=nullptr) { //CUANDO SE AGOTA EL TIEMPO DE VIDA DE UNA EXPLOSION
					if (board[i][j]->killMe) 
						board[i][j] = nullptr;
				}
			}
		}
	}

	std::set<int> myPositions;
	int positions = 0;
	for (std::deque<Powerup*>::iterator a=powerupList.begin(); a!=powerupList.end(); ++a){
		if (users.first->doCollide(**a)) {
			if ((*a)->isHelmet)
				users.first->putHelmet();
			else
				users.first->putBoots();
			myPositions.insert(positions);
		}
		else if (users.second->doCollide(**a)) {
			if ((*a)->isHelmet)
				users.second->putHelmet();
			else
				users.second->putBoots();
			myPositions.insert(positions);
		}
		positions++;
	}

	for (std::set<int>::reverse_iterator a=myPositions.rbegin(); a!=myPositions.rend(); ++a)
		powerupList.erase(powerupList.begin() + *a);

	if (users.first->myBomb != nullptr && bombList.first == nullptr) {
		bombList.first = users.first->myBomb;
		bombList.first->photo.placeholder.x = static_cast<int>((users.first->getCenter().first / 48.0f))*48;
		bombList.first->photo.placeholder.y = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
	}
	else if (users.first->myBomb == nullptr && bombList.first == nullptr && !users.first->canBomb) {
		users.first->canBomb = true;
	}

	if (users.second->myBomb != nullptr && bombList.second == nullptr) {
		bombList.second = users.second->myBomb;
		bombList.second->photo.placeholder.x = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
		bombList.second->photo.placeholder.y = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
	}
	else if (users.second->myBomb == nullptr && bombList.second == nullptr && !users.second->canBomb) {
		users.second->canBomb = true;
	}

	if (bombList.first != nullptr) {
		
		bombList.first->update();
		if (bombList.first->collideWithPlayer) {
			users.first->correctPosition(bombList.first);
		}
		else if (!bombList.first->doCollide(*users.first)) {
			bombList.first->collideWithPlayer = true;
		}
		users.second->correctPosition(bombList.first);

		if (bombList.first->isExploding) {
			bool isBlock = false;
			for (int j = 0; j < 3 && !isBlock; ++j) {
				if (board[bombList.first->getCenter().first / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48] != nullptr) {
					switch (board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->harm();
						board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
						board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.first->photo.placeholder.x + j * 48;
						board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.first->photo.placeholder.y);
						users.first->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.first->photo.placeholder.x + j*48;
							powerupList.back()->photo.placeholder.y = (bombList.first->photo.placeholder.y);
						}
						break;
					case TIPO_CASILLA::PLAYER2:{
						if (!users.second->isInmune) {
							users.first->score += 100;
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER1:
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;	
						}
						break;
					}
				}
				else {
					board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
					board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.first->photo.placeholder.x + j*48;
					board[bombList.first->photo.placeholder.x / 48 + j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.first->photo.placeholder.y);
				}
			}
			isBlock = false;
			for (int j = 1; j < 3 && !isBlock; ++j) {
				if (board[bombList.first->getCenter().first / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48] != nullptr) {
					switch (board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->harm();
						board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
						board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.first->photo.placeholder.x - j * 48;
						board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.first->photo.placeholder.y);
						users.first->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.first->photo.placeholder.x - j*48;
							powerupList.back()->photo.placeholder.y = (bombList.first->photo.placeholder.y);
						}
						break;
					case TIPO_CASILLA::PLAYER2: {
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.first->score += 100;
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER1:
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48] = new Explosion();
					board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.first->photo.placeholder.x - j*48;
					board[bombList.first->photo.placeholder.x / 48 - j][(bombList.first->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.first->photo.placeholder.y);
				}
			}
			isBlock = false;
			for (int j = 1; j < 3 && !isBlock; ++j) {
				if (board[bombList.first->getCenter().first / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j] != nullptr) {
					switch (board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->harm();
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j] = new Explosion();
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = bombList.first->photo.placeholder.x;
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = (bombList.first->photo.placeholder.y) + j*48;
						users.first->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.first->photo.placeholder.x;
							powerupList.back()->photo.placeholder.y = (bombList.first->photo.placeholder.y) + j * 48;
						}
						break;
					case TIPO_CASILLA::PLAYER2: {
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.first->score += 100;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->harm();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER1:
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->harm();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j] = new Explosion();
					board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = bombList.first->photo.placeholder.x;
					board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = (bombList.first->photo.placeholder.y) + j*48;
				}
			}
			isBlock = false;
			for (int j = 1; j < 3 && !isBlock; ++j) {
				if (board[bombList.first->getCenter().first / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j] != nullptr) {
					switch (board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->harm();
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j] = new Explosion();
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = bombList.first->photo.placeholder.x;
						board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = (bombList.first->photo.placeholder.y) - j*48;
						users.first->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.first->photo.placeholder.x;
							powerupList.back()->photo.placeholder.y = (bombList.first->photo.placeholder.y) - j * 48;
						}
						break;
					case TIPO_CASILLA::PLAYER2: {
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.first->score += 100;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->harm();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER1:
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->harm();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j] = new Explosion();
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = localX;
							board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j] = new Explosion();
					board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = bombList.first->photo.placeholder.x;
					board[bombList.first->photo.placeholder.x / 48][(bombList.first->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = (bombList.first->photo.placeholder.y ) - j*48;
				}
			}
			bombList.first = nullptr;
			delete users.first->myBomb;
			users.first->myBomb = nullptr;
		}

	}
		/////////////////////////////////////////
	if (bombList.second != nullptr) {

		bombList.second->update();
		if (bombList.second->collideWithPlayer) {
			users.second->correctPosition(bombList.second);
		}
		else if (!bombList.second->doCollide(*users.second)) {
			bombList.second->collideWithPlayer = true;
		}
		users.first->correctPosition(bombList.second);

		if (bombList.second->isExploding) {
			bool isBlock = false;
			for (int j = 0; j < 3 && !isBlock; ++j) {
				if (board[bombList.second->getCenter().first / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48] != nullptr) {
					switch (board[bombList.second->getCenter().first / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->harm();
						board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
						board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.second->photo.placeholder.x + j * 48;
						board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.second->photo.placeholder.y);
						users.second->score += 15;
						isBlock = true;
						break;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.second->photo.placeholder.x + j*48;
							powerupList.back()->photo.placeholder.y = (bombList.second->photo.placeholder.y);
						}
					case TIPO_CASILLA::PLAYER1: {
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.second->score += 100;
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER2:
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
					board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.second->photo.placeholder.x + j * 48;
					board[bombList.second->photo.placeholder.x / 48 + j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.second->photo.placeholder.y);
				}
			}
			isBlock = false;
			for (int j = 1; j < 3 && !isBlock; ++j) {
				if (board[bombList.second->getCenter().first / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48] != nullptr) {
					switch (board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->harm();
						board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
						board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.second->photo.placeholder.x - j * 48;
						board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.second->photo.placeholder.y);
						users.second->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.second->photo.placeholder.x - j * 48;
							powerupList.back()->photo.placeholder.y = (bombList.second->photo.placeholder.y);
						}
						break;
					case TIPO_CASILLA::PLAYER1: {
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.second->score += 100;
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER2:
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->harm();
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48] = new Explosion();
					board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.x = bombList.second->photo.placeholder.x - j * 48;
					board[bombList.second->photo.placeholder.x / 48 - j][(bombList.second->photo.placeholder.y - 80) / 48]->photo.placeholder.y = (bombList.second->photo.placeholder.y);
				}
			}
			isBlock = false;
			for (int j = 1; j < 3 && !isBlock; ++j) {
				if (board[bombList.second->getCenter().first / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j] != nullptr) {
					switch (board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->harm();
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j] = new Explosion();
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = bombList.second->photo.placeholder.x;
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = (bombList.second->photo.placeholder.y) + j*48;
						users.second->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.second->photo.placeholder.x;
							powerupList.back()->photo.placeholder.y = (bombList.second->photo.placeholder.y) + j*48;
						}
						break;
					case TIPO_CASILLA::PLAYER1: {
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.second->score += 100;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->harm();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER2:
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->harm();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j] = new Explosion();
					board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.x = bombList.second->photo.placeholder.x;
					board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 + j]->photo.placeholder.y = (bombList.second->photo.placeholder.y) + j * 48;
				}
			}
			isBlock = false;
			for (int j = 1; j < 3 && !isBlock; ++j) {
				if (board[bombList.second->getCenter().first / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j] != nullptr) {
					switch (board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->whoIam) {
					case TIPO_CASILLA::BLOQUE:
						isBlock = true;
						break;
					case TIPO_CASILLA::MURO:
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->harm();
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j] = new Explosion();
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = bombList.second->photo.placeholder.x;
						board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = (bombList.second->photo.placeholder.y) - j * 48;
						users.second->score += 15;
						isBlock = true;
						if (rand() % 100 <= 20) {
							powerupList.push_back(new Powerup);
							powerupList.back()->photo.placeholder.x = bombList.second->photo.placeholder.x;
							powerupList.back()->photo.placeholder.y = (bombList.second->photo.placeholder.y) - j * 48;
						}
						break;
					case TIPO_CASILLA::PLAYER1: {
						if (!users.first->isInmune) {
							int localX = static_cast<int>((users.first->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.first->getCenter().second - 80) / 48.0f)) * 48 + 80;
							users.second->score += 100;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->harm();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = localY;
						}
						break;
					}
					case TIPO_CASILLA::PLAYER2:
						if (!users.second->isInmune) {
							int localX = static_cast<int>((users.second->getCenter().first / 48.0f)) * 48;
							int localY = static_cast<int>(((users.second->getCenter().second - 80) / 48.0f)) * 48 + 80;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->harm();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j] = new Explosion();
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = localX;
							board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = localY;
						}
						break;
					}
				}
				else {
					//PARA QUE LA EXPLOSION NO REPELA AL PJ
					board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j] = new Explosion();
					board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.x = bombList.second->photo.placeholder.x;
					board[bombList.second->photo.placeholder.x / 48][(bombList.second->photo.placeholder.y - 80) / 48 - j]->photo.placeholder.y = (bombList.second->photo.placeholder.y) - j * 48;

				}
			}
			bombList.second = nullptr;
			delete users.second->myBomb;
			users.second->myBomb = nullptr;
		}

	}



	if (users.first->vidas <= 0 || users.second->vidas <= 0 || interfaz->timer <= 0) {
		if (auxTime == 256)
			auxTime = interfaz->timer;
		if (auxTime - interfaz->timer >= 1000) {
			bool empate = false;
			if (users.first->vidas <= 0 && users.second->vidas <= 0) {
				//EMPATE
				empate = true;
				std::cout << "Habéis empatado!" << std::endl;
			}
			else if (users.first->vidas <= 0) {
				//GANA PJ2
				std::cout << "Enhorabuena Jugador2. Has ganado!" << std::endl;
			}
			else if (users.second->vidas <= 0) {
				//GANA PJ1
				std::cout << "Enhorabuena Jugador1. Has ganado!" << std::endl;
			}
			else {
				//LOS DOS ESTÁN VIVOS
				if (users.first->score == users.second->score) {
					//EMPATE
					empate = true;
					std::cout << "Habéis empatado!" << std::endl;
				}
				else if (users.first->score < users.second->score) {
					//GANA PJ2
					std::cout << "Enhorabuena Jugador2. Has ganado!" << std::endl;
				}
				else {
					//GANA PJ1
					std::cout << "Enhorabuena Jugador1. Has ganado!" << std::endl;
				}
			}

			if (!empate) {
				std::cout << "Introduce tu nombre: " << std::endl;
				std::string winnerName;
				std::getline(std::cin, winnerName);
			}
			CurrentGameState = GAME_STATE::MENU;
		}
	}
}

void Play::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->renderIMG(bg.id, bg.placeholder);
	
		users.first->draw();
		users.second->draw();

	if (bombList.first != nullptr)
		bombList.first->draw();
	if (bombList.second != nullptr)
		bombList.second->draw();

	for (Powerup* a : powerupList) {
		a->draw();
	}

	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 13; ++j) {
			if (board[i][j] != nullptr) {
				board[i][j]->draw();
			}
		}
	}



	interfaz->draw();
}

void Play::LeerXml()
{
	rapidxml::xml_document<> XMLdoc;
	std::ifstream archivo("../../dep/FicheroXML.xml");
	std::stringstream buff;
	buff << archivo.rdbuf();
	archivo.close();
	std::string ContenidoBuffer(buff.str());
	XMLdoc.parse<0>(&ContenidoBuffer[0]);

	rapidxml::xml_node<> *Root = XMLdoc.first_node();
	rapidxml::xml_attribute<> *pAttr;
	char* Comparador;
	char* NameAtt;
	std::string nameInnerNode;
	std::pair <int, int> coor;


	for (rapidxml::xml_node<> *Pnode = Root->first_node("Level"); Pnode; Pnode = Pnode->next_sibling()) //accedemos al nodo level
	{
		
		for (pAttr = Pnode->first_attribute("id"); pAttr; pAttr = pAttr->next_attribute()) //accedemos al primer atributo de level que es id
		{			
			Comparador = pAttr->name();

			if (atoi(pAttr->value()) == 1 && CurrentGameState == GAME_STATE::STAY) //si pongo en vez de STAY PLAY1 no entra en el if proque antes de que llegue a este ya ha cambiado el game state
			{				

				for (rapidxml::xml_node<> *InnerNode = Pnode->first_node("Destructible");; InnerNode->next_sibling()) //accedemos al tercer nodo dentro del xml, el cual es Destructible
				{					
					nameInnerNode = InnerNode->name();
					//std::cout << InnerNode->name();
					
						if (nameInnerNode == "Destructible") //el cout lo hace bien, se llama asi y no entra en el if, bucle infinito wtf
						{
							for (rapidxml::xml_node<> *InnerInnerNode = InnerNode->first_node("Wall"); InnerInnerNode; InnerInnerNode = InnerInnerNode->next_sibling()) //accedemos al primer nodo dentro del nodo destructible, el cual es wall
							{
								//std::cout << InnerInnerNode->name();

								for (rapidxml::xml_attribute<> *InnerAttr = InnerInnerNode->first_attribute("i"); InnerAttr; InnerAttr = InnerAttr->next_attribute())//accedemos al primer atributo de wall
								{
									std::cout << InnerAttr->value();
									NameAtt = InnerAttr->name();

									if (NameAtt == "i") //si NameAtt vale i, es la primera coordenada, nos guardamos en el primer int del pair este numero, para no perderlo en la siguiente iteraçao
									{
										coor.first = atoi(InnerAttr->value());
									}
									if (NameAtt == "j") //si e sj, estamos en la segunda coordenada, la guardamos en el segundo int del pair y le pasamos a board estos int
									{
										coor.second = atoi(InnerAttr->value());
										board[coor.first][coor.second] = new Muro();
									}
								}
							}
						}
						if (nameInnerNode == "Fixed")
						{

						}
				}
			}
			if (Comparador == "time")
			{
				interfaz->timer = atoi(pAttr->value());
			}
			if (Comparador == "lives")
			{
				users.first->vidas = users.second->vidas = atoi(pAttr->value());
			}
			

			//if (atoi(pAttr->value()) == 2 && CurrentGameState == GAME_STATE::PLAY2)
			//{
			//	for (rapidxml::xml_node<> *InnerNode = Root->first_node("Destructible"); InnerNode; InnerNode = InnerNode->next_sibling()) //accedemos al tercer nodo dentro del xml, el cual es Destructible
			//	{
			//		for (rapidxml::xml_node<> *InnerInnerNode = InnerNode->first_node("Wall"); InnerInnerNode; InnerInnerNode = InnerInnerNode->next_sibling()) //accedemos al primer nodo dentro del nodo destructible, el cual es wall
			//		{
			//			for (rapidxml::xml_attribute<> *InnerAttr = InnerInnerNode->first_attribute("i"); InnerAttr; InnerAttr = InnerAttr->next_attribute())//accedemos al primer atributo de wall
			//			{
			//				NameAtt = InnerAttr->name();

			//				if (NameAtt == "i") //si NameAtt vale i, es la primera coordenada, nos guardamos en el primer int del pair este numero, para no perderlo en la siguiente iteraçao
			//				{
			//					coor.first = atoi(InnerAttr->value());
			//				}
			//				if (NameAtt == "j") //si e sj, estamos en la segunda coordenada, la guardamos en el segundo int del pair y le pasamos a board estos int
			//				{
			//					coor.second = atoi(InnerAttr->value());
			//					board[coor.first][coor.second] = new Bloque();
			//				}
			//			}
			//		}

			//		for (rapidxml::xml_node<> *InnerNode = Root->first_node("Fixed"); InnerNode;)
			//		{

			//		}

			//	}
			//}
			//if (Comparador == "time")
			//{
			//	interfaz->timer = atoi(pAttr->value());
			//}
			//if (Comparador == "lives")
			//{
			//	users.first->vidas = users.second->vidas = atoi(pAttr->value());
			//}
		}
	}


	//for (rapidxml::xml_node<> *pNode = Root->first_node("Level"); pNode; pNode = pNode->next_sibling())
	//{
	//	Buff = pNode->first_attribute("lives");
	//	//for (rapidxml::xml_attribute<> *pAttrb = pNode->first_attribute(); pAttrb; pAttrb = pAttrb->next_attribute())
	//	//{
	//	//	
	//	//	//switch (pAttrb->)
	//	//	//{
	//	//	//case 'id':
	//	//	//	if (pAttrb->value == '1')
	//	//	//	{
	//	//	//		//cargar el nivel 1
	//	//	//	}
	//	//	//	break;

	//	//	//case 'time':
	//	//	//	/*timer = atoi(pAttrb->value()));*/ 
	//	//	//	break;

	//	//	//case 'lives':
	//	//	//	users.first->vidas = users.second->vidas = atoi(pAttrb->value());
	//	//	//	break;
	//	//	//}
	//	//}

	//	for (rapidxml::xml_node<> *myInnerNode = pNode->first_node(); myInnerNode; myInnerNode = myInnerNode->next_sibling())
	//	{
	//		if (myInnerNode->name() == "Destructible")
	//		{
	//			for (rapidxml::xml_attribute<> *pAt = pNode->first_attribute(); pAt; pAt = pAt->next_attribute())
	//			{

	//			}
	//		}
	//		
	//	}
	//}
}
