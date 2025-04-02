#pragma once
#include "Modifiers.h"

class CharacterData {
private:
	float x, y;
	short int width, height;

	float healthMod, damageMod, moveMod, expMod, aoeMod;
	short int armorMod;

	short int baseHp, currentHp, effectiveHp, xp, xpToNext, level;
public:
	void setSizes(float readX, float readY, int readWidth, int readHeight);
	void setMods();
	void move(float msX, float msY);
	float getMoveMod();
	float getX();
	float getY();
	short int getCurrentHp();
	short int getEffectiveHp();
	void setHp(short int readHp);
	void changeHp(short int readChange);
	void recalculateHp();
	short int getXp();
	short int getXpToNext();
	void increaseXp(short int readXp);
	short int getLevel();
	short int getWidth();
};
