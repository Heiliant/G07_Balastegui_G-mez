#include "Button.h"



Button::Button()
{
	leftClick = false;

	message.path = PATH_SAIYAN;
	message.size = 25;
	message.msg = "HelloWorld";
	message.color = SDL_Color{ 0, 0, 0, 255 };
	message.placeHolder.x = 0;
	message.placeHolder.y = 0;
	message.placeHolder.w = 100;
	message.placeHolder.h = 100;

	message.id=Renderer::Instance()->loadText(message);
}


Button::~Button()
{
}

bool Button::isClicked()
{
	if (isHovered()) {
		if (leftClick) {
			return true;
		}
	}
	return false;
}

bool Button::isHovered()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < (message.placeHolder.x + message.placeHolder.w) && x > (message.placeHolder.x)) {
		if (y < (message.placeHolder.y + message.placeHolder.h) && y > (message.placeHolder.y)) {
			return true;
		}
	}
	return false;
}

void Button::resetText(Text newcomer) {
	message.path = newcomer.path;
	message.size = newcomer.size;
	message.msg = newcomer.msg;
	message.color = newcomer.color;
	message.placeHolder.x = newcomer.placeHolder.x;
	message.placeHolder.y = newcomer.placeHolder.y;
	message.placeHolder.w = newcomer.placeHolder.w;
	message.placeHolder.h = newcomer.placeHolder.h;

	Renderer::Instance()->loadText(message, message.id);
}

void Button::eventHandler( SDL_Event evnt)
{
	int a = 0;
		switch (evnt.type) {
			case SDL_MOUSEBUTTONDOWN:
				switch (evnt.button.button) {
				case SDL_BUTTON_LEFT:
					leftClick = true;
					break;
				}
				break;
			default:
				leftClick = false;
		}
	
}

void Button::update()
{
    if (isHovered())
	{
	}	
}

void Button::draw() //le pasamos una variable de tipo Text porque los botones tienen Text, que contiene el color, el rectangulo, el path, el tamaño, el texto etc
{
	Renderer::Instance()->renderIMG(message.id, message.placeHolder);
}
