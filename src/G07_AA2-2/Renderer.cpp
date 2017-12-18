#include "Renderer.h"

Renderer::Renderer()
{
	m_window = SDL_CreateWindow("BOMBERMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG};
	
	nextKey = 0;
}

Renderer * Renderer::Instance()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer;
	}

	return renderer;
}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	TTF_Quit();
	SDL_Quit();
}

void Renderer::Clear()
{
	SDL_RenderClear(m_renderer); 
}

void Renderer::Render() 
{ 
	SDL_RenderPresent(m_renderer); 
}

int Renderer::loadIMG(std::string path)
{
	SDL_Texture* tempTex = IMG_LoadTexture(m_renderer, path.c_str());
	m_images[nextKey] = tempTex;
	return nextKey++;
}

int Renderer::loadText(Text text)
{
	TTF_Font *ttfFont = TTF_OpenFont(text.path.c_str(), text.size);
	SDL_Surface* mySurface = TTF_RenderText_Blended(ttfFont, text.msg.c_str(), text.color);
	SDL_Texture* myTexture = SDL_CreateTextureFromSurface(m_renderer, mySurface);

	m_images[nextKey] = myTexture;
	
	SDL_FreeSurface(mySurface);
	TTF_CloseFont(ttfFont);

	return nextKey++; 
}

int Renderer::loadSpriteSheet(std::string path, int spritesInX, int spritesInY) {
	SDL_Texture* myTexture = IMG_LoadTexture(m_renderer, path.c_str());
	int w, h;
	int lmao = 0;
	SDL_QueryTexture(myTexture, NULL, NULL, &w, &h);
	w /= spritesInX;
	h /= spritesInY;

	m_images[nextKey] = myTexture;
	m_spriteData[nextKey] = std::make_pair(w, h);
	return nextKey++;
}

void Renderer::loadText(Text text, int id) {
	TTF_Font *ttfFont = TTF_OpenFont(text.path.c_str(), text.size);
	SDL_Surface* mySurface = TTF_RenderText_Blended(ttfFont, text.msg.c_str(), text.color);
	SDL_Texture* myTexture = SDL_CreateTextureFromSurface(m_renderer, mySurface);

	TTF_CloseFont(ttfFont);
	m_images[id] = myTexture;
	SDL_FreeSurface(mySurface);
}

void Renderer::renderIMG(int id, const SDL_Rect &rect)
{
	SDL_RenderCopy(m_renderer, m_images[id], nullptr, &rect);
}

void Renderer::renderSprite(int id, const SDL_Rect & rect, std::pair<int, int> spriteCoor)
{
	SDL_Rect local;
	local.x=m_spriteData[id].first*spriteCoor.first;
	local.y=m_spriteData[id].second*spriteCoor.second;
	local.w = m_spriteData[id].first;
	local.h = m_spriteData[id].second;

	SDL_RenderCopy(m_renderer, m_images[id], &local, &rect);
}


Renderer* Renderer::renderer = nullptr;



