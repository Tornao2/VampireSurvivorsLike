#pragma once
#include <SFML/Graphics.hpp>

struct EnemyDataNode {
	short int width, height;
	short int baseHp, currentHp;
	sf::Sprite* sprite;
};

static EnemyDataNode enemyArray[] = {
	{16, 24, 100, 100, nullptr}
};

class EnemyData {
	float x, y;
	EnemyDataNode enemyStats;
public:
	void giveStats(int enemyId, float readX, float readY);
	EnemyDataNode* getEnemyDataNode();
};