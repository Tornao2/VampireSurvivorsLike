#pragma once
#include <SFML/Graphics.hpp>

struct EnemyDataNode {
	sf::Vector2f size;
	int armor, xp;
	float baseHp, damage, move;
};

static EnemyDataNode enemyArray[] = {
	{{16, 24}, 0, 10, 100, 6, 0.5f}, 
	{{16, 24}, 20, 11, 150, 6, 0.5f},
	{ { 16, 24 }, 30, 11, 200, 7, 1.0f },
	{ { 16, 24 }, 10, 12, 200, 7, 1.5f },
	{ { 16, 24 }, 40, 13, 100, 8, 1.0f},
	{ { 16, 24 }, 40, 14,150, 8, 0.8f },
	{ { 16, 24 }, 50, 15,300, 7, 0.8f },
	{ { 16, 24 }, 10, 16, 500, 5, 0.6f },
	{ { 16, 24 }, 0, 20, 500, 7, 0.8f },
	{ { 16, 24 }, 50, 22, 100, 8, 1.0f }
};

class EnemyData {
	sf::Vector2f pos;
	float currentHp;
	EnemyDataNode enemyStats;
	sf::Sprite* sprite;
	bool isBoss;
public:
	void giveStats(int enemyId, sf::Vector2f readPos, bool readIsBoss);
	EnemyDataNode* getEnemyDataNode();
	sf::Vector2f getSize();
	sf::Vector2f getPos();
	float getDamage();
	void move(sf::Vector2f ms);
	void changeHealthBy(float readChange);
	float getHealth();
	void clearSprite();
	sf::Sprite* getSprite();
	void setSprite(sf::Sprite* readSprite);
	int getXpForKill();
	bool getIfBoss();
};