#pragma once
#include "Items.h"
#include "Projectiles.h"

static int weaponMaxDelays[10] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

static bool weaponCanEvolve[10] = {true, false, true, true, true, false, true, false, false, false};

static std::pair<int, int> evolutionRequirement[10] = {{11, 7}, {0, 0}, {12, 8}, {14, 3}, {15, 5}, {0, 0}, {13, 12}, {0, 0}, {0, 0}, {0, 0}};

class Weapon {
	ItemInfo basicInfo;
	sf::Sprite* projectileSprite;
	int delay, currentDelay, nextEvolution, requiredItemId;
	bool canEvolve;
public:
	Weapon();
	void setHidden();
	ItemInfo* getBasicInfo();
	sf::Sprite* getProjectileSprite();
	void deleteSprites();
	void setProjectileSprite(sf::Sprite* readSprite);
	void decrementDelay();
	void resetDelay();
	int getDelay();
};