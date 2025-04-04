#pragma once
#include "Scene.h"
#include "Modifiers.h"

class UpgradeScene : public Scene {
	int spriteHolderIndex;
	int selectedRow, selectedColumn;
	unsigned char upgrRowsAmount;
	unsigned char* colAmounts;
	Modifiers modifiers;
	void refreshSelection();
public:
	using Scene::Scene;
	void loadModifiers();
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};