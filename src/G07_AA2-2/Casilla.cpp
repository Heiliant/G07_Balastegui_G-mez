#include "Casilla.h"



Casilla::Casilla()
{
	photo.path = PATH_ITEMS;
	photo.id = Renderer::Instance()->loadSpriteSheet(photo.path, 3, 2);

	photo.placeholder.w = photo.placeholder.h= 48;

	killMe = false;
}


Casilla::~Casilla()
{
}

void Casilla::harm()
{
}

void Casilla::update()
{
}

void Casilla::draw()
{
}

std::pair<int, int> Casilla::getCenter() {
	int one, two;
	one = photo.placeholder.x + photo.placeholder.w / 2;
	two = photo.placeholder.y + photo.placeholder.h / 2;
	return (std::make_pair( one, two ));
}

bool Casilla::doCollide(Casilla other) {
	int xDist = abs(getCenter().first - other.getCenter().first);
	int yDist = abs(getCenter().second - other.getCenter().second);
	return(xDist < (photo.placeholder.w / 2 + other.photo.placeholder.w / 2) && yDist < (photo.placeholder.h / 2 + other.photo.placeholder.h / 2));
}

void Casilla::correctPosition(Casilla* other)
{
	if (doCollide(*other)) {
		int xDist = abs(getCenter().first - other->getCenter().first);
		int yDist = abs(getCenter().second - other->getCenter().second);


		if (xDist - (photo.placeholder.w / 2 + other->photo.placeholder.w / 2) > yDist - (photo.placeholder.h / 2 + other->photo.placeholder.h / 2)) {

			if (getCenter().first > other->getCenter().first) {
				photo.placeholder.x += abs(xDist - (photo.placeholder.w / 2 + other->photo.placeholder.w / 2));
			}
			else {
				photo.placeholder.x -= abs(xDist - (photo.placeholder.w / 2 + other->photo.placeholder.w / 2));
			}
		}
		else {
			if (getCenter().second > other->getCenter().second) {
				photo.placeholder.y += abs(yDist - (photo.placeholder.h / 2 + other->photo.placeholder.h / 2));
			}
			else {
				photo.placeholder.y -= abs(yDist - (photo.placeholder.h / 2 + other->photo.placeholder.h / 2));
			}
		}
	}
}

