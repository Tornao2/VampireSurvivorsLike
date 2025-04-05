#pragma once
#include <SFML/Graphics.hpp>

struct EnemyDataNode {
	sf::Vector2f size;
	int armor;
	float baseHp, damage, move;
	sf::Sprite* sprite;
};

static EnemyDataNode enemyArray[] = {
	{{16, 24}, 0, 100, 3, 0.5,nullptr}
};

class EnemyData {
	sf::Vector2f pos;
	float currentHp;
	EnemyDataNode enemyStats;
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
};