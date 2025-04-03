#pragma once
#include "Scene.h"
#include "CharacterData.h"
#include <iomanip>

class PlaySpace : public Scene {
	int enemyHolderIndex, playerHolderIndex, chunkHolderIndex, hudHolderIndex;
	int mapNumber, charNumber;
	int lastToggleTime = 0;
	CharacterData playerData;
	sf::Clock timer;
	void moveWithCollision();
	void setTimer();
	void checkChunks();
	void drawHud();
	bool respawnEnemies();
	void randomizePos(int& x, int& y);
public:
	using Scene::Scene;
	void setMapAndChar(int readMap, int readChar);
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	bool realTimeLogic();
	CharacterData getPlayerData();
};