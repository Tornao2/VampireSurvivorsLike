#include "CharacterData.h"

CharacterData::CharacterData() {
	std::vector<int> weaponIds = { 1, 0 ,0 };
	itemInfos = {
		{0, 0, 0, nullptr},
		{0, 0, 0, nullptr},
		{0, 0, 0, nullptr}
	};
}

CharacterDetails getCharacterStats(int index) {
	return charArray[index];
}

void CharacterData::setSizes(sf::Vector2f readPos, sf::Vector2i readSize) {
	pos = readPos;
	size = readSize;
}

void CharacterData::setMods() {
	xpToNext = 100;
	xp = 0;
	level = 1;
	invincibilityFrame = 0;
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
	currentHp = getEffectiveMaxHp();
}

void CharacterData::setBaseStats(int charId) {
	baseStats = charArray[charId];
}

void CharacterData::move(sf::Vector2f ms) {
	pos += ms;
}

sf::Vector2f CharacterData::getPos() {
	return pos;
}

float CharacterData::getCurrentHp() {
	return currentHp;
}

float CharacterData::getEffectiveMaxHp() {
	return baseStats.baseHp * healthMod + baseStats.baseHp;
}

int CharacterData::getXp() {
	return xp;
}

int CharacterData::getXpToNext() {
	return xpToNext;
}

void CharacterData::increaseXp(int readXp) {
	xp += (int)(readXp * getEffectiveXpMod());
	while (xp >= xpToNext) {
		level++;
		xp -= xpToNext;
		xpToNext *=  1.2;
		currentHp = getEffectiveMaxHp();
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
			if (readChange + getEffectiveArmorMod() < 0) {
				currentHp += readChange + getEffectiveArmorMod();
				invincibilityFrame = 5;
				if (currentHp < 0)
					currentHp = 0;
			}
		}
	}
	else {
		currentHp += readChange;
		if (currentHp > getEffectiveMaxHp())
			currentHp = getEffectiveMaxHp();
	}
}

sf::Vector2i CharacterData::getSize() {
	return size;
}

void CharacterData::decrementInvincibility() {
	if (invincibilityFrame)
		invincibilityFrame--;
}

float CharacterData::getEffectiveMs() {
	return moveMod * baseStats.baseMs + baseStats.baseMs;
}

float CharacterData::getEffectiveDamage() {
	return damageMod + baseStats.baseDamage;
}

float CharacterData::getEffectiveXpMod() {
	return expMod + baseStats.baseExp;
}

int CharacterData::getEffectiveArmorMod() {
	return armorMod + baseStats.baseArmor;
}

sf::Vector2i CharacterData::getOffsets() {
	return baseStats.offset;
}

void CharacterData::setSlippage(sf::Vector2f readSlipping) {
	slippage = readSlipping;
}

sf::Vector2f CharacterData::getSlippage() {
	return slippage;
}

int CharacterData::getUsedWeaponSlots() {
	return usedWeaponSlots;
}

int CharacterData::getUsedItemSlots() {
	int count = 0;
	for (itemInfo item : itemInfos)
		if (item.currentLevel != 0)
			count++;
	return count;
}

std::vector<int> CharacterData::getWeaponIds() {
	return weaponIds;
}

std::vector<itemInfo>& CharacterData::getItemIds() {
	return itemInfos;
}

std::vector<bool> CharacterData::getIfEvolve() {
	return weaponCanEvolve;
}