#pragma once
#include "Modifiers.h"
#include <SFML/System/Vector2.hpp>
#include "Unlocks.h"
#include "Items.h"

struct CharacterDetails {
	float baseHp, baseMs, baseDamage, baseExp;
	int baseArmor;
	sf::Vector2i offset;
};

static CharacterDetails charArray[NUMBEROFCHARS] = {
	{100.0f, 2.0f, 1.0f, 1.0f, 0, {0, 0}},
	{120.0f, 1.8f, 1.0f, 1.0f, 1, {16, 0}},
	{80.0f, 2.5f, 1.1f, 1.1f, 1, {32, 0}},
	{200.0f, 1.5f, 0.95f, 0.95f, 2, {48, 0}}
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
	std::vector<int> weaponIds;
	std::vector<itemInfo> itemInfos;
	std::vector<bool> weaponCanEvolve = { false, false, false };
	sf::Vector2f slippage;
public:
	CharacterData();
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
	std::vector<int> getWeaponIds();
	std::vector<itemInfo>& getItemIds();
	std::vector<bool> getIfEvolve();
	void addItem(int readId, int readLevel, sf::Sprite* readSprite);
	void changeStats(int readId, int readLevel);
	int getHowManyItem();
};
