#include "CharacterData.h"

void CharacterData::setSizes(sf::Vector2f readPos, sf::Vector2f readSize) {
	pos = readPos;
	size = readSize;
	baseHp = 100;
	effectiveHp = 100;
	xpToNext = 100;
	xp = 0;
	level = 1;
	invincibilityFrame = 0;
	baseMs = 2;
}

void CharacterData::setMods() {
	Modifiers mod;
	mod.loadModifiersFromFile();
	ModifierNode* tempNode = mod.getNodeByName("Health%");
	healthMod = tempNode->effectStrength * tempNode->currentLevel; 
	tempNode = mod.getNodeByName("Damage%");
	damageMod = tempNode->effectStrength * tempNode->currentLevel;
	tempNode = mod.getNodeByName("Move%");
	moveMod = tempNode->effectStrength * tempNode->currentLevel;
	tempNode = mod.getNodeByName("Exp%");
	expMod = tempNode->effectStrength * tempNode->currentLevel;
	tempNode = mod.getNodeByName("Armor");
	armorMod = (int) tempNode->effectStrength * tempNode->currentLevel;
	tempNode = mod.getNodeByName("AOE%");
	aoeMod = tempNode->effectStrength * tempNode->currentLevel;
	effectiveHp = (int) (baseHp * healthMod + baseHp);
}

void CharacterData::move(sf::Vector2f ms) {
	pos += ms;
}

float CharacterData::getMoveMod() {
	return moveMod;
}

sf::Vector2f CharacterData::getPos() {
	return pos;
}

float CharacterData::getCurrentHp() {
	return currentHp;
}

int CharacterData::getEffectiveHp() {
	return effectiveHp;
}

void CharacterData::recalculateHp() {
	effectiveHp = (int) (baseHp + healthMod * baseHp);
}

int CharacterData::getXp() {
	return xp;
}

int CharacterData::getXpToNext() {
	return xpToNext;
}

void CharacterData::increaseXp(int readXp) {
	xp += readXp;
	while (xp >= xpToNext) {
		level++;
		xp -= xpToNext;
		xpToNext *= (int) 1.2;
	}
}

int CharacterData::getLevel() {
	return level;
}

void CharacterData::setHp(float readHp) {
	currentHp = readHp;
}

void CharacterData::changeHp(float readChange) {
	if (readChange < 0) {
		if (!invincibilityFrame) {
			if (readChange + armorMod < 0) {
				currentHp += readChange + armorMod;
				invincibilityFrame = 5;
				if (currentHp < 0)
					currentHp = 0;
			}
		}
	}
	else {
		currentHp += readChange;
		if (currentHp > effectiveHp)
			currentHp = effectiveHp;
	}
}

sf::Vector2f CharacterData::getSize() {
	return size;
}

void CharacterData::decrementInvincibility() {
	if (invincibilityFrame)
		invincibilityFrame--;
}

float CharacterData::getEffectiveMs() {
	return moveMod * baseMs + baseMs;
}