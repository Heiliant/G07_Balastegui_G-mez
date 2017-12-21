#pragma once
#include <String>
#include <SDL.h>

enum class GAME_STATE{MENU, RANKING, PLAY1, PLAY2, STAY}; //asi podemos saber en que estado se encuentra el juego desde cualquier clase

enum class TIPO_CASILLA{MURO, BLOQUE, PLAYER1, PLAYER2, EXPLOSION, NADA};

using Color = struct Color { Uint8 r; Uint8 g; Uint8 b; Uint8 a; };

struct Text
{
	std::string path; //path de la fuente
    std::string msg;  //lo que se quiere escribir
	int size;		  //tamaño de la fuente
	SDL_Rect placeHolder; //rectángulo en el que se escribirá
	SDL_Color color;		//color del texto
	int id;
};

struct Rect {
	int x;
	int y;
	int w;
	int h;
};

struct Image {
	std::string path;
	SDL_Rect placeholder; //esto tiene que ser un sdl rect  en vez de tipo struct rect porque sino no podemos pasarlo como argumento a las funciones del renderer
	int id;
};

struct Score {
	std::string name;
	int points;
	Text face;
};

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 704;

static const char* PATH_BG= "../../res/img/bgGame.jpg"; 
static const char* PATH_SAIYAN = "../../res/ttf/saiyan.ttf";
static const char* PATH_GAMEOVER = "../../res/ttf/game_over.ttf";
static const char* PATH_ITEMS = "../../res/img/items.png";
static const char* PATH_PJ1 = "../../res/img/player1.png";
static const char* PATH_PJ2 = "../../res/img/player2.png";
static const char* PATH_EXPLOSION = "../../res/img/explosion.png";

const float PLAYTIME = 70000;

const int HUD_X_MARGIN = 40;