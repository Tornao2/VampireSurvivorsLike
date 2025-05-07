#pragma once
#include "Items.h"
#include "Projectiles.h"

static std::vector<std::vector<float>> weaponBaseStats = { 
	{20, 25, 3, 1000}, 
	{80, 500, 2, 1000},
	{30, 50, 3, 300},
	{50, 75, 7, 1000},
	{75, 300, 7, 400},
	{20, 200, 6, 1000},
	{20, 150, 5, 700},
	{15, 150, 6, 700},
	{45, 150, 8, 1000},
	{70, 500, 10, 1000}};

static bool weaponCanEvolve[10] = {true, true, true, true, true, false, true, false, false, false};

static std::pair<int, int> evolutionRequirement[10] = {{11, 7}, {11, 6}, {12, 8}, {14, 3}, {15, 5}, {0, 0}, {13, 12}, {0, 0}, {0, 0}, {0, 0}};

class Weapon {
	ItemInfo basicInfo;
	int delay, currentDelay, nextEvolution, requiredItemId, baseRange;
	float baseDmg, baseMs;
	bool canEvolve;
public:
	Weapon();
	void setHidden();
	ItemInfo* getBasicInfo();
	void decrementDelay();
	void resetDelay();
	int getDelay();
	bool getIfCanEvolve();
	int getRequiredItemEvolution();
	int getNextEvolution();
	void reset();
	std::vector<float> getStatsForProjectile();
	void changeDamage(float readValue);
	void changeMs(float readValue);
	void changeRange(int readValue);
	void changeFirerate(int readValue);
	int getBaseDelay();
};