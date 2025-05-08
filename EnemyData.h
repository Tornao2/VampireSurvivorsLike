#pragma once
#include <SFML/Graphics.hpp>

struct EnemyDataNode {
	sf::Vector2i offset;
	int armor, xp;
	float baseHp, damage, move;
};

static EnemyDataNode enemyArray[] = {
	{{0, 0}, 0, 10, 80, 8, 0.7f}, 
	{{16, 0}, 20, 11, 120, 8, 0.7f},
	{ { 32, 0 }, 30, 11, 150, 10, 1.0f },
	{ { 48, 0 }, 10, 12, 150, 10, 1.5f },
	{ { 64, 0 }, 40, 13, 120, 12, 1.0f},
	{ { 0, 24 }, 40, 14,150, 12, 0.8f },
	{ { 16, 24 }, 50, 15,200, 12, 1.1f },
	{ { 32, 24 }, 10, 16, 300, 8, 1.0f },
	{ { 48, 24 }, 0, 20, 300, 10, 1.2f },
	{ { 64, 24 }, 50, 22, 100, 15, 1.5f }
};

class EnemyData {
	sf::Vector2f pos;
	sf::Vector2f size;
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
	void setPosition(sf::Vector2f readPosition);
	sf::Vector2i getOffset();
};
