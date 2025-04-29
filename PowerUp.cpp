#include "PowerUp.h"

PowerUp::PowerUp(int readId, sf::Vector2f readPosition, sf::Sprite* readSprite) {
	id = readId;
	position = readPosition;
	size = { 10, 10 };
	timeLeft = 360;
	sprite = readSprite;
}

int PowerUp::getId() {
	return id;
}

bool PowerUp::decrementTimeLeft() {
	timeLeft--;
	return (timeLeft == 0);
}

sf::Vector2i PowerUp::getSize() {
	return size;
}

sf::Vector2f PowerUp::getPos() {
	return position;
}

sf::Sprite* PowerUp::getSprite() {
	return sprite;
}

void PowerUp::deleteSprite() {
	delete sprite;
	sprite = nullptr;
}
