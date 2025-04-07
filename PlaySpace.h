#pragma once
#include "Scene.h"
#include "CharacterData.h"

class PlaySpace : public Scene {
	int playerHolderIndex, hudHolderIndex;
	int mapNumber, charNumber;
	int lastSpawnTime = 0;
	CharacterData playerData;
	sf::Clock timer;
	void move();
	void moveProjectiles();
	void setTimer();
	void checkChunks();
	void drawHud();
	void respawnEnemies();
	sf::Vector2f randomizePos();
	void checkEnemyCollision();
	void moveEnemies();
	void checkEnemyHp();
	void weaponLogic();
	void checkProjectileCollision();
public:
	using Scene::Scene;
	void setMapAndChar(int readMap, int readChar);
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	bool realTimeLogic();
	CharacterData getPlayerData();
};