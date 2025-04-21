#pragma once
#include "Scene.h"
#include "CharacterData.h"

class PlayChoice : public Scene {
	int* selectedMap, *selectedPlayer;
	int selectedRow, spriteHolderIndex;
	std::vector<bool> unlockedChars;
	std::vector<bool> unlockedMaps;
	void refreshSelection();
	void refreshCharacterStats();
public:
	using Scene::Scene;
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	void setPointers(int* readMap, int* readPlayer);
};