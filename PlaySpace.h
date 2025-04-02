#pragma once
#include "Scene.h"
#include "CharacterData.h"
#include <iomanip>

class PlaySpace : public Scene {
	int enemyHolderIndex, playerHolderIndex, chunkHolderIndex, hudHolderIndex;
	int mapNumber, charNumber;
	CharacterData playerData;
	sf::Clock timer;
	void moveWithCollision();
	void setTimer();
	void checkChunks();
	void drawHud();
public:
	using Scene::Scene;
	void setMapAndChar(int readMap, int readChar);
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	void realTimeLogic();
	CharacterData getPlayerData();
};