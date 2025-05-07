#pragma once
#include <SFML/Graphics.hpp>
#define M_PI 3.14159265358979323846f

class Projectiles {
	sf::Sprite* sprite = nullptr;
	float effectiveDamange, effectiveRange;
	sf::Vector2f actualMs;
	sf::Vector2i size;
	sf::Vector2f pos;
public:
	Projectiles(sf::Sprite* readSprite, float damage, float range, float ms, sf::Vector2f readPos, sf::Vector2f readEndPos, sf::Vector2i readSize);
	sf::Vector2i getSize();
	sf::Vector2f getPos();
	float getDamage();
	void clearSprite();
	void move();
	sf::Sprite* getSprite();
	void rotate(sf::Vector2f readTargetPos, float readMs);
};