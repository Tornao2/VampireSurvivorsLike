#include "Weapons.h"

ItemInfo* Weapon::getBasicInfo() {
	return &basicInfo;
}

void Weapon::setHidden() {
	delay = weaponMaxDelays[basicInfo.itemId - 6];
	canEvolve = weaponCanEvolve[basicInfo.itemId - 6];
	nextEvolution = evolutionRequirement[basicInfo.itemId - 6].first;
	requiredItemId = evolutionRequirement[basicInfo.itemId - 6].second;
}

Weapon::Weapon() {
	basicInfo = { 0, 0, -1 };
	projectileSprite = nullptr;
}

sf::Sprite* Weapon::getProjectileSprite() {
	return projectileSprite;
}

void Weapon::deleteSprites() {
	if (projectileSprite != nullptr)
		delete projectileSprite;
}

void Weapon::setProjectileSprite(sf::Sprite* readSprite) {
	projectileSprite = readSprite;
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
