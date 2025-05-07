#include "CharacterData.h"

CharacterDetails getCharacterStats(int index) {
	return charArray[index];
}

bool CharacterData::getLastXDir() {
	return lastXRight;
}

bool CharacterData::getLastYDir() {
	return lastYDown;
}

CharacterData::CharacterData() {
	itemInfos = {
		{0, 0, -1},
		{0, 0, -1},
		{0, 0, -1}
	};
	for (int i = 0; i < 3; i++) 
		weaponInfo.push_back(Weapon());
}

void CharacterData::addItem(int readId, int readLevel) {
	if (readLevel == 1) {
		for (ItemInfo& item : itemInfos) {
			if (item.currentLevel == 0) {
				item.currentLevel = 1;
				item.maxLevel = 5;
				item.itemId = readId;
				break;
			}
		}
	}
	else {
		for (ItemInfo& item : itemInfos) {
			if (item.itemId == readId) {
				item.currentLevel++;
				break;
			}
		}
	}
	changeStats(readId, readLevel);
}

void CharacterData::addWeapon(int readId, int readLevel, sf::Texture* readProjectileSprite) {
	Weapon weapon;
	if (readLevel == 1) {
		for (Weapon& item : weaponInfo) {
			if (item.getBasicInfo()->currentLevel == 0) {
				weapon = item;
				item.getBasicInfo()->currentLevel = 1;
				item.getBasicInfo()->maxLevel = 5;
				item.getBasicInfo()->itemId = readId;
				item.setHidden();
				break;
			}
		}
	}
	else {
		for (Weapon& item : weaponInfo) {
			if (item.getBasicInfo()->itemId == readId) {
				weapon = item;
				item.getBasicInfo()->currentLevel++;
				break;
			}
		}
	}
	changeWeaponStats(readId, readLevel, weapon);
}

void CharacterData::chestLogic(sf::Texture* readProjectileSprite) {
	for (Weapon& weapon : weaponInfo) {
		if (weapon.getIfCanEvolve() && weapon.getBasicInfo()->currentLevel == weapon.getBasicInfo()->maxLevel) {
			int requiredItem = weapon.getRequiredItemEvolution();
			bool ifFound = false;
			for (Weapon& checkedWeapon : weaponInfo) 
				if (requiredItem == checkedWeapon.getBasicInfo()->itemId) {
					ifFound = true;
					if (checkedWeapon.getBasicInfo()->itemId == 6 || checkedWeapon.getBasicInfo()->itemId == 7) 
						checkedWeapon.reset();
				}
			for (ItemInfo& item : itemInfos) 
				if (item.itemId == requiredItem) 
					ifFound = true;
			if (ifFound == false)
				break;
			int nextId = weapon.getNextEvolution();
			weapon = Weapon();
			weapon.getBasicInfo()->currentLevel = 1;
			weapon.getBasicInfo()->maxLevel = 1;
			weapon.getBasicInfo()->itemId = nextId;
			weapon.setHidden();
			changeWeaponStats(nextId, 1, weapon);
			return;
		}
	}
	increaseXp(getXpToNext());
}

void CharacterData::changeStats(int readId, int readLevel) {
	switch (readId) {
	case 1:
		switch (readLevel) {
			case 1:
				healthMod += 0.2;
				break;
			case 2:
				healthMod += 0.2;
				break;
			case 3:
				healthMod += 0.15;
				break;
			case 4:
				baseStats.baseHp += 20;
				break;
			case 5:
				healthMod += 0.3;
				break;
			}
		break;
	case 2:
		switch (readLevel) {
			case 1:
				damageMod += 0.1;
				break;
			case 2:
				damageMod += 0.1;
				break;
			case 3:
				damageMod += 0.15;
				break;
			case 4:
				damageMod += 0.15;
				break;
			case 5:
				damageMod += 0.15;
				break;
		}
		break;
	case 3:
		switch (readLevel) {
			case 1:
				moveMod += 0.05;
				break;
			case 2:
				moveMod += 0.10;
				break;
			case 3:
				moveMod += 0.15;
				break;
			case 4:
				baseStats.baseMs += 0.1;
				break;
			case 5:
				moveMod += 0.10;
				break;
			}
		break;
	case 4:
		switch (readLevel) {
			case 1:
				armorMod += 1;
				break;
			case 2:
				armorMod += 1;
				break;
			case 3:
				armorMod += 1;
				break;
			case 4:
				armorMod += 1;
				break;
			case 5:
				armorMod += 2;
				break;
			}
		break;
	case 5:
		switch (readLevel) {
			case 1:
				expMod += 0.05;
				break;
			case 2:
				expMod += 0.05;
				break;
			case 3:
				expMod += 0.10;
				break;
			case 4:
				expMod += 0.05;
				break;
			case 5:
				expMod += 0.10;
				break;
			}
		break;
	
	}
}

void CharacterData::changeWeaponStats(int readId, int readLevel, Weapon& readWeapon) {
	switch (readId) {
		case 6:
			switch (readLevel) {
				case 2:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
				case 3:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[1] * 1.2);
					break;
				case 4:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
				case 5:
					readWeapon.changeFirerate(readWeapon.getBaseDelay() - 5);
					break;
			}
			break;
		case 7:
			switch (readLevel) {
				case 2:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[1] * 1.2);
					break;
				case 3:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[1] * 1.2);
					break;
				case 4:
					readWeapon.changeFirerate(readWeapon.getBaseDelay() - 5);
					break;
				case 5:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[1] * 1.2);
					break;
			}
			break;
		case 8:
			switch (readLevel) {
				case 2:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
				case 3:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
				case 4:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[2] * 1.2);
					break;
				case 5:
					readWeapon.changeFirerate(readWeapon.getBaseDelay() - 5);
					break;
			}
			break;
		case 9:
			switch (readLevel) {
				case 2:
					readWeapon.changeFirerate(readWeapon.getBaseDelay() - 5);
					break;
				case 3:
					readWeapon.changeFirerate(readWeapon.getBaseDelay() - 5);
					break;
				case 4:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
				case 5:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
			}
			break;
		case 10:
			switch (readLevel) {
				case 2:
					readWeapon.changeFirerate(readWeapon.getBaseDelay() - 5);
					break;
				case 3:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[2] * 1.2);
					break;
				case 4:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[2] * 1.2);
					break;
				case 5:
					readWeapon.changeDamage(readWeapon.getStatsForProjectile()[0] * 1.2);
					break;
			}
			break;
	}
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
	if (ms.x > 0)
		lastXRight = true;
	else if (ms.x < 0)
		lastXRight = false;
	if (ms.y > 0)
		lastYDown = true;
	else if (ms.y < 0)
		lastYDown = false;
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
	int count = 0;
	for (Weapon weapon : weaponInfo)
		if (weapon.getBasicInfo()->currentLevel == weapon.getBasicInfo()->maxLevel)
			count++;
	return count;
}

int CharacterData::getUsedItemSlots() {
	int count = 0;
	for (const ItemInfo& item : itemInfos)
		if (item.currentLevel == item.maxLevel)
			count++;
	return count;
}

std::vector<Weapon>* CharacterData::getWeaponInfo() {
	return &weaponInfo;
}

std::vector<ItemInfo>* CharacterData::getItemIds() {
	return &itemInfos;
}

std::vector<bool> CharacterData::getIfEvolve() {
	return weaponCanEvolve;
}

int CharacterData::getHowManyItem() {
	int count = 0;
	for (const ItemInfo& item : itemInfos)
		if (item.currentLevel != 0)
			count++;
	return count;
}

int CharacterData::getHowManyWeapons() {
	int count = 0;
	for (Weapon item : weaponInfo)
		if (item.getBasicInfo()->currentLevel != 0)
			count++;
	return count;
}
