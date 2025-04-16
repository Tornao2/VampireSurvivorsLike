#include "Projectiles.h"

Projectiles::Projectiles(sf::Sprite* readSprite, float damageMod, sf::Vector2f readPos, sf::Vector2f readEndPos, int projectileId) {
	sprite = readSprite;
	damage = baseProjectileStats.at(projectileId).at(0) * damageMod;
	pos = readPos;
	size = { baseProjectileStats.at(projectileId).at(3), baseProjectileStats.at(projectileId).at(4)};
	sf::Vector2f targetVec = readEndPos - readPos;
	float length = std::sqrt(targetVec.x * targetVec.x + targetVec.y * targetVec.y);
	sf::Vector2f normalizedVec = targetVec / length;
	ms = baseProjectileStats.at(projectileId).at(1) * normalizedVec;
	range = baseProjectileStats.at(projectileId).at(2);
}

sf::Vector2f Projectiles::getSize() {
	return size;
}

sf::Vector2f Projectiles::getPos() {
	return pos;
}

float Projectiles::getDamage() {
	return damage;
}

void Projectiles::move() {
	pos = pos + ms;
	sprite->move(ms);
}

void Projectiles::clearSprite() {
	delete sprite;
	sprite = nullptr;
}

sf::Sprite* Projectiles::getSprite() {
	return sprite;
}