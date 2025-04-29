#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PowerUp {
	int id;
	sf::Sprite* sprite;
	sf::Vector2f position;
	sf::Vector2i size;
	int timeLeft;
public:
	PowerUp(int readId, sf::Vector2f readPosition, sf::Sprite* readSprite);
	int getId();
	bool decrementTimeLeft();
	sf::Vector2i getSize();
	sf::Vector2f getPos();
	sf::Sprite* getSprite();
	void deleteSprite();
};