#include "EnemyData.h"

void EnemyData::giveStats(int enemyId, float readX, float readY){
	x = readX;
	y = readY;
	enemyStats = enemyArray[enemyId];
}

EnemyDataNode* EnemyData::getEnemyDataNode() {
	return &enemyStats;
}