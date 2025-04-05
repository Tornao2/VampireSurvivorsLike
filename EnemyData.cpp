#include "EnemyData.h"

void EnemyData::giveStats(int enemyId, sf::Vector2f readPos){
	pos = readPos;
	enemyStats = enemyArray[enemyId];
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
	enemyStats.sprite->move(ms * enemyStats.move);
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
	delete enemyStats.sprite;
	enemyStats.sprite = nullptr;
}