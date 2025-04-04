#pragma once
#include <SFML/Graphics.hpp>

struct EnemyDataNode {
	short int width, height;
	short int baseHp, currentHp, damage;
	float move;
	sf::Sprite* sprite;
};

static EnemyDataNode enemyArray[] = {
	{16, 24, 100, 100, 3, 0.5,nullptr}
};

class EnemyData {
	float x, y;
	EnemyDataNode enemyStats;
public:
	void giveStats(int enemyId, float readX, float readY);
	EnemyDataNode* getEnemyDataNode();
	short int getWidth();
	short int getHeight();
	float getX();
	float getY();
	short int getDamage();
	void move(float readX, float readY);
};