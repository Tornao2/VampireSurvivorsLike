#include "CharacterData.h"

void CharacterData::setSizes(float readX, float readY, int readWidth, int readHeight) {
	x = readX;
	y = readY;
	width = readWidth;
	height = readHeight;
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
	armorMod = (short int) tempNode->effectStrength * tempNode->currentLevel;
	tempNode = mod.getNodeByName("AOE%");
	aoeMod = tempNode->effectStrength * tempNode->currentLevel;
	effectiveHp = (short int) (baseHp * healthMod + baseHp);
}

void CharacterData::move(float msX, float msY) {
	x += msX;
	y += msY;
}

float CharacterData::getMoveMod() {
	return moveMod;
}

float CharacterData::getX() {
	return x;
}

float CharacterData::getY() {
	return y;
}

short int CharacterData::getCurrentHp() {
	return currentHp;
}

short int CharacterData::getEffectiveHp() {
	return effectiveHp;
}

void CharacterData::recalculateHp() {
	effectiveHp = (short int) (baseHp + healthMod * baseHp);
}

short int CharacterData::getXp() {
	return xp;
}

short int CharacterData::getXpToNext() {
	return xpToNext;
}

void CharacterData::increaseXp(short int readXp) {
	xp += readXp;
	while (xp >= xpToNext) {
		level++;
		xp -= xpToNext;
		xpToNext *= (short int) 1.2;
	}
}

short int CharacterData::getLevel() {
	return level;
}

void CharacterData::setHp(short int readHp) {
	currentHp = readHp;
}

void CharacterData::changeHp(short int readChange) {
	if (!invincibilityFrame) {
		currentHp += readChange;
		invincibilityFrame = 5;
		if (currentHp < 0)
			currentHp = 0;
	}
}

short int CharacterData::getWidth() {
	return width;
}

short int CharacterData::getHeight() {
	return height;
}

void CharacterData::decrementInvincibility() {
	if (invincibilityFrame)
		invincibilityFrame--;
}

float CharacterData::getEffectiveMs() {
	return moveMod * baseMs + baseMs;
}