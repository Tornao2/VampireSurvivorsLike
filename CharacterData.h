#pragma once
#include "Modifiers.h"
#include <SFML/System/Vector2.hpp>

class CharacterData {
private:
	sf::Vector2f pos, size;

	float healthMod, damageMod, moveMod, expMod, aoeMod;
	int armorMod;

	float currentHp;
	int baseHp, baseMs, effectiveHp, xp, xpToNext, level, invincibilityFrame;
public:
	void setSizes(sf::Vector2f readPos, sf::Vector2f readSize);
	void setMods();
	void move(sf::Vector2f ms);
	float getMoveMod();
	sf::Vector2f getPos();
	float getCurrentHp();
	int getEffectiveHp();
	void setHp(float readHp);
	void changeHp(float readChange);
	void recalculateHp();
	int getXp();
	int getXpToNext();
	void increaseXp(int readXp);
	int getLevel();
	sf::Vector2f getSize();
	void decrementInvincibility();
	float getEffectiveMs();
	float getDamageMod();
};
