#include "Weapons.h"

ItemInfo* Weapon::getBasicInfo() {
	return &basicInfo;
}

void Weapon::setHidden() {
	delay = weaponBaseStats[basicInfo.itemId - 6][0];
	baseDmg = weaponBaseStats[basicInfo.itemId - 6][1];
	baseMs = weaponBaseStats[basicInfo.itemId - 6][2];
	baseRange = weaponBaseStats[basicInfo.itemId - 6][3];
	canEvolve = weaponCanEvolve[basicInfo.itemId - 6];
	nextEvolution = evolutionRequirement[basicInfo.itemId - 6].first;
	requiredItemId = evolutionRequirement[basicInfo.itemId - 6].second;
}

void Weapon::reset() {
	basicInfo = { 0, 0, -1 };
}

Weapon::Weapon() {
	basicInfo = { 0, 0, -1 };
}

void Weapon::decrementDelay() {
	currentDelay--;
}

void Weapon::resetDelay() {
	currentDelay = delay;
}

int Weapon::getDelay() {
	return currentDelay;
}

int Weapon::getBaseDelay() {
	return delay;
}

bool Weapon::getIfCanEvolve() {
	return canEvolve;
}

int Weapon::getRequiredItemEvolution() {
	return requiredItemId;
}

int Weapon::getNextEvolution() {
	return nextEvolution;
}

std::vector<float> Weapon::getStatsForProjectile() {
	return {baseDmg, baseMs, (float) baseRange};
}

void Weapon::changeDamage(float readValue) {
	baseDmg = readValue;
}

void Weapon::changeFirerate(int readValue) {
	delay = readValue;
}