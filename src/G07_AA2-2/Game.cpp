#include "Game.h"



Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	currentScene = new Menu();
	

	srand(time(NULL));

	//LEER EL ARCHIVO BINARIO Y ALMACENAR SUS VALORES EN LA toAddList
}


Game::~Game()
{
}

void Game::run()
{
	while (currentScene->isRunning())
	{
		updateScene();

		Renderer::Instance()->Clear();
		currentScene->eventHandler();	
		currentScene->update();
		currentScene->draw();

		if (currentScene->winnerN != "notaname" && currentScene->winnerS != -1) {
			toAddList.push_back(std::make_pair(currentScene->winnerN, currentScene->winnerS));
		}
		Renderer::Instance()->Render();
	}

	//ESCRIBIR EL ARCHIVO BINARIO Y ALMACENAR LOS VALORES DE LA toAddList EN ÉL
}

void Game::updateScene()
{
	switch (currentScene->CurrentGameState)
	{
	case GAME_STATE::MENU:   //si pongo esto no funciona nada del sistema de escenas, y no se porque, si lo pongo dentro de un if dentro del case ranking, funcionan todas las escenas menos la del ranking, enytra en esta y sale automaticamente, sin esperar a que le des al boton de back
		delete currentScene;
		currentScene = new Menu();
		currentScene->CurrentGameState = GAME_STATE::STAY;
		break;
	case GAME_STATE::RANKING:
		delete currentScene;
		currentScene = new Ranking(toAddList);
		currentScene->CurrentGameState = GAME_STATE::STAY;
		break;
	case GAME_STATE::PLAY1:
		delete currentScene;
		currentScene = new Play(1);
		currentScene->CurrentGameState = GAME_STATE::STAY;
		break;
	case GAME_STATE::PLAY2:
		delete currentScene;
		currentScene = new Play(2);
		currentScene->CurrentGameState = GAME_STATE::STAY;
		break;
	default:
		break;
	}
}




