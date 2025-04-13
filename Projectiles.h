#pragma once
#include <SFML/Graphics.hpp>

//Damage, ms, range, sizes
static std::vector<std::vector<float>> baseProjectileStats = {
	{1000, 3, 600, 8, 8}
};

class Projectiles {
	sf::Sprite* sprite = nullptr;
	float damage;
	sf::Vector2f pos, ms, size;
	float range;
public:
	Projectiles(sf::Sprite* readSprite, float damageMod, sf::Vector2f readPos, sf::Vector2f readEndPos, int projectileId);
	sf::Vector2f getSize();
	sf::Vector2f getPos();
	float getDamage();
	void clearSprite();
	void move();
	sf::Sprite* getSprite();
};