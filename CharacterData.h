#pragma once
#include "Modifiers.h"
#include "Unlocks.h"
#include "Weapons.h"

struct CharacterDetails {
	float baseHp, baseMs, baseDamage, baseExp;
	int baseArmor;
	sf::Vector2i offset;
};

static CharacterDetails charArray[NUMBEROFCHARS] = {
	{80.0f, 2.0f, 1.0f, 1.0f, 0, {0, 0}},
	{100.0f, 1.8f, 1.0f, 1.0f, 1, {16, 0}},
	{60.0f, 2.5f, 1.1f, 1.1f, 1, {32, 0}},
	{140.0f, 1.5f, 0.95f, 0.95f, 2, {48, 0}}
};

CharacterDetails getCharacterStats(int index);

class CharacterData {
private:
	sf::Vector2f pos;
	sf::Vector2i size;
	float healthMod, damageMod, moveMod, expMod;
	int armorMod;
	CharacterDetails baseStats;
	float currentHp;
	int xp, xpToNext, level, invincibilityFrame, usedWeaponSlots = 3;
	std::vector<Weapon> weaponInfo;
	std::vector<ItemInfo> itemInfos;
	std::vector<bool> weaponCanEvolve = { false, false, false };
	sf::Vector2f slippage;
	bool lastXRight, lastYDown;
public:
	CharacterData();
	bool getLastXDir();
	bool getLastYDir();
	void setSizes(sf::Vector2f readPos, sf::Vector2i readSize);
	void setMods();
	void setBaseStats(int charId);
	void move(sf::Vector2f ms);
	sf::Vector2f getPos();
	float getCurrentHp();
	void setHp(float readHp);
	void changeHp(float readChange);
	int getXp();
	int getXpToNext();
	void increaseXp(int readXp);
	int getLevel();
	sf::Vector2i getSize();
	void decrementInvincibility();
	float getEffectiveMaxHp();
	float getEffectiveMs();
	float getEffectiveDamage();
	float getEffectiveXpMod();
	int getEffectiveArmorMod();
	sf::Vector2i getOffsets();
	void setSlippage(sf::Vector2f readSlipping);
	sf::Vector2f getSlippage();
	int getUsedWeaponSlots();
	int getUsedItemSlots();
	std::vector<Weapon>* getWeaponInfo();
	std::vector<ItemInfo>* getItemIds();
	std::vector<bool> getIfEvolve();
	void addWeapon(int readId, int readLevel);
	void addItem(int readId, int readLevel);
	void changeStats(int readId, int readLevel);
	void changeWeaponStats(int readId, int readLevel, Weapon& readWeapon);
	int getHowManyItem();
	int getHowManyWeapons();
	void chestLogic(sf::Texture* readProjectileSprite);
};
