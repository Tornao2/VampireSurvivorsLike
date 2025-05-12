#include "EnemyData.h"

void EnemyData::giveStats(int enemyId, sf::Vector2f readPos, bool readIsBoss){
	pos = readPos;
	enemyStats = enemyArray[enemyId];
	size = { 16, 24 };
	if (readIsBoss) {
		enemyStats.armor *= 3;
		enemyStats.damage *= 2;
		enemyStats.baseHp *= 10;
		enemyStats.move *= 1.3;
		size = { 32, 48 };
		enemyStats.xp *= 10;
	}
	isBoss = readIsBoss;
	currentHp = (int) enemyStats.baseHp;
}

sf::Vector2f EnemyData::getSize() {
	return size;
}

sf::Vector2f EnemyData::getPos() {
	return pos;
}

float EnemyData::getDamage() {
	return enemyStats.damage;
}

void EnemyData::move(sf::Vector2f ms) {
	pos += ms * enemyStats.move;
	sprite->setPosition({ std::round(pos.x), std::round(pos.y) });
}

void EnemyData::changeHealthBy(float readChange) {
	if (readChange < 0) {
		if (readChange + enemyStats.armor < 0) {
			currentHp += readChange + enemyStats.armor;
			if (currentHp < 0)
				currentHp = 0;
		}
	}
	else {
		currentHp += readChange;
		if (currentHp > enemyStats.baseHp)
			currentHp = enemyStats.baseHp;
	}
}

float EnemyData::getHealth() {
	return currentHp;
}

void EnemyData::clearSprite() {
	delete sprite;
	sprite = nullptr;
}

sf::Sprite* EnemyData::getSprite() {
	return sprite;
}

void EnemyData::setSprite(sf::Sprite* readSprite) {
	sprite = readSprite;
}

int EnemyData::getXpForKill() {
	return enemyStats.xp;
}

bool EnemyData::getIfBoss() {
	return isBoss;
}

void EnemyData::setPosition(sf::Vector2f readPosition) {
	pos = readPosition;
	sprite->setPosition(readPosition);
}

sf::Vector2i EnemyData::getOffset() {
	return enemyStats.offset;
}