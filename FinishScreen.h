#pragma once
#include "Scene.h"
#include "Modifiers.h"
#include "Unlocks.h"

class FinishScreen: public Scene{
	int spriteHolderIndex;
	void refreshSelection();
	int coins;
	bool unlocked = false;
public:
	using Scene::Scene;
	void setCoins(int readCoins, int chosenMap, int chosenChar);
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};