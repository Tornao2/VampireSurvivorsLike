#include "EnemyData.h"

void EnemyData::giveStats(int enemyId, sf::Vector2f readPos, bool readIsBoss){
	pos = readPos;
	enemyStats = enemyArray[enemyId];
	if (readIsBoss) {
		enemyStats.armor *= 5;
		enemyStats.damage *= 4;
		enemyStats.baseHp *= 20;
		enemyStats.move *= 1.4;
		enemyStats.size = { 32, 48 };
		enemyStats.xp *= 10;
	}
	isBoss = readIsBoss;
	currentHp = (int) enemyStats.baseHp;
}

EnemyDataNode* EnemyData::getEnemyDataNode() {
	return &enemyStats;
}

sf::Vector2f EnemyData::getSize() {
	return enemyStats.size;
}

sf::Vector2f EnemyData::getPos() {
	return pos;
}

float EnemyData::getDamage() {
	return enemyStats.damage;
}

void EnemyData::move(sf::Vector2f ms) {
	pos += ms * enemyStats.move;
	sprite->move(ms * enemyStats.move);
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