#include "Projectiles.h"

Projectiles::Projectiles(sf::Sprite* readSprite, float damage, float range, float ms, sf::Vector2f readPos, sf::Vector2f readEndPos, sf::Vector2i readSize) {
	sprite = readSprite;
	effectiveDamage = damage;
	effectiveRange = range;
	pos = readPos;
	size = readSize;
	rotate(readEndPos, ms);
}

void Projectiles::rotate(sf::Vector2f readTargetPos, float readMs) {
	sf::Vector2f direction = readTargetPos - pos;
	sf::Angle angle = (sf::radians(std::atan2(direction.y, direction.x)));
	sprite->setRotation(angle);
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitDir = (length != 0) ? direction / length : sf::Vector2f(0, 0);
	actualMs = unitDir * readMs;
}

sf::Vector2i Projectiles::getSize() {
	return size;
}

sf::Vector2f Projectiles::getPos() {
	return pos;
}

float Projectiles::getDamage() {
	return effectiveDamage;
}

void Projectiles::move() {
	pos = pos + actualMs;
	sprite->move(actualMs);
}

void Projectiles::clearSprite() {
	delete sprite;
	sprite = nullptr;
}

sf::Sprite* Projectiles::getSprite() {
	return sprite;
}