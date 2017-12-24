#include "Game.h"



Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	currentScene = new Menu();
	LeerBinario();

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
			toAddList.emplace_back(std::make_pair(currentScene->winnerN, currentScene->winnerS));
		}
		Renderer::Instance()->Render();
	}

	EscribirBinario();

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

void Game::LeerBinario()
{
		std::ifstream fentrada("../../res/Ranking.bin", std::ios_base::binary | std::ios_base::app);

		int capacity;

		fentrada.read(reinterpret_cast<char *>(&capacity), sizeof(int));
		std::cout << capacity;

		for (int i=0; i<capacity; i++)
		{
			size_t stringSize = 0;
			toAddList.push_back(std::make_pair("", 0));

			fentrada.read(reinterpret_cast<char *>(&stringSize), sizeof(size_t));//lee el tamaño del string (va bien)

			char* aux = new char[stringSize + 1];

			fentrada.read(aux, stringSize);
			aux[stringSize] = '\0';
			toAddList.back().first = aux;
			fentrada.read(reinterpret_cast<char *>(&toAddList.back().second), sizeof(int));
		}		

		fentrada.close();
}

void Game::EscribirBinario()
{
		std::ofstream fsalida("../../res/Ranking.bin", std::ios::out | std::ios::binary);
		int capacity = toAddList.size();
		std::cout << capacity;
	
		fsalida.write(reinterpret_cast<char *>(&capacity), sizeof(int));
		for (std::vector <std::pair<std::string, int>>::iterator i = toAddList.begin(); i != toAddList.end(); i++)
		{
			size_t localStringSize = i->first.size();
			fsalida.write(reinterpret_cast<char *>(&localStringSize), sizeof(size_t));//escribir tamaño del string
			fsalida.write((i->first.c_str()), i->first.size());//escribir contenido del string

			fsalida.write(reinterpret_cast<char *>(&i->second), sizeof(i->second));//escribir score
		}

		
		fsalida.close();
}




