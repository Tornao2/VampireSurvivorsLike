#pragma once
#include "Scene.h"
#include "Unlocks.h"

class PlayChoice : public Scene {
	int* selectedMap, *selectedPlayer;
	int selectedRow, spriteHolderIndex;
	std::vector<bool> unlockedChars;
	std::vector<bool> unlockedMaps;
	void refreshSelection();
public:
	using Scene::Scene;
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	void setPointers(int* readMap, int* readPlayer);
};