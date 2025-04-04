#include "EnemyData.h"

void EnemyData::giveStats(int enemyId, float readX, float readY){
	x = readX;
	y = readY;
	enemyStats = enemyArray[enemyId];
}

EnemyDataNode* EnemyData::getEnemyDataNode() {
	return &enemyStats;
}

short int EnemyData::getWidth() {
	return enemyStats.width;
}

short int EnemyData::getHeight() {
	return enemyStats.height;
}

float EnemyData::getX() {
	return x;
}

float EnemyData::getY() {
	return y;
}

short int EnemyData::getDamage() {
	return enemyStats.damage;
}

void EnemyData::move(float readX, float readY) {
	x += readX * enemyStats.move;
	y += readY * enemyStats.move;
	enemyStats.sprite->move({ readX * enemyStats.move , readY * enemyStats.move });
}