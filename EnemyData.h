#pragma once
#include <SFML/Graphics.hpp>

struct EnemyDataNode {
	sf::Vector2f size;
	int armor;
	float baseHp, damage, move;
};

static EnemyDataNode enemyArray[] = {
	{{16, 24}, 0, 100, 6, 0.5f}, 
	{{16, 24}, 20, 150, 6, 0.5f},
	{ { 16, 24 }, 30, 200, 7, 1.0f },
	{ { 16, 24 }, 10, 200, 7, 1.5f },
	{ { 16, 24 }, 40, 100, 8, 1.0f},
	{ { 16, 24 }, 40, 150, 8, 0.8f },
	{ { 16, 24 }, 50, 300, 7, 0.8f },
	{ { 16, 24 }, 10, 500, 5, 0.6f },
	{ { 16, 24 }, 0, 500, 7, 0.8f },
	{ { 16, 24 }, 50, 100, 8, 1.0f }
};

class EnemyData {
	sf::Vector2f pos;
	float currentHp;
	EnemyDataNode enemyStats;
	sf::Sprite* sprite;
public:
	void giveStats(int enemyId, sf::Vector2f readPos);
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
};