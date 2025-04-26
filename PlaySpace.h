#pragma once
#include "Scene.h"
#include "CharacterData.h"

class PlaySpace : public Scene {
	int playerHolderIndex, hudHolderIndex, pauseMenuHolderIndex, mapNumber, charNumber;
	int lastSpawnTime = -10, lastFireTime = 0, pauseBreak = 3, pauseButtonIndex = 0;
	bool paused = false;
	CharacterData playerData;
	sf::Clock timer;
	sf::Vector2f determineMovement();
	void terrainCollision(sf::Vector2f moveStep);
	void movementLogic();
	void moveProjectiles();
	void setTimer();
	void chunkLogic();
	void setHud();
	void respawnEnemies();
	sf::Vector2f randomizePos();
	void checkEnemyCollision();
	void moveEnemies();
	void checkEnemyHp();
	void weaponLogic();
	void checkProjectileCollision();
	void initPauseMenu();
	void cleanPauseMenu();
	void pauseButtonFocus();
	void calculateSlippage(sf::Vector2f readMovement);
public:
	using Scene::Scene;
	void setMapAndChar(int readMap, int readChar);
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	bool realTimeLogic();
	CharacterData getPlayerData();
	int getCoins();
	bool getPaused();
	void decrementPauseTime();
};