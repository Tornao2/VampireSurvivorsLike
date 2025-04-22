#pragma once
#include "Modifiers.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Unlocks.h"

struct CharacterDetails {
	float baseHp, baseMs, baseDamage, baseAoe, baseExp;
	int baseArmor;
	sf::Vector2i offset;
};

static CharacterDetails charArray[NUMBEROFCHARS] = {
	{100, 2, 1, 1, 1, 0, {0, 0}},
	{120, 1.8, 1, 1, 1, 1, {16, 0}},
	{80, 2.5, 1.1, 1.1, 1.1, 1, {32, 0}},
	{200, 1.5, 0.95, 0.95, 0.95, 2, {48, 0}}
};

CharacterDetails getCharacterStats(int index);

class CharacterData {
private:
	sf::Vector2f pos;
	sf::Vector2i size;
	float healthMod, damageMod, moveMod, expMod, aoeMod;
	int armorMod;
	CharacterDetails baseStats;
	float currentHp;
	int xp, xpToNext, level, invincibilityFrame;
public:
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
	float getEffectiveAoeMod();
	int getEffectiveArmorMod();
	sf::Vector2i getOffsets();
};
