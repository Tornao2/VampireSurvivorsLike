#pragma once
#include "Scene.h"
#include "CharacterData.h"

class PlaySpace : public Scene {
	bool enemyWiggleHelper[16][15];
	int playerHolderIndex, hudHolderIndex, additionalMenuIndex, mapNumber, charNumber;
	int lastSpawnTime = -10, lastFireTime = 0, pauseBreak = 3, buttonIndex = 0, availableChoices = 0, additionalCoins = 0, levelDifference = 0;
	bool paused = false, levelingUp = false;
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
	void powerUpLogic();
	void usePowerUp(int readId);
	void cleanPauseMenu();
	void pauseButtonFocus();
	void levelButtonFocus();
	void calculateSlippage(sf::Vector2f readMovement);
	bool initLevelUp();
	void cleanLevelMenu();
public:
	using Scene::Scene;
	void setMapAndChar(int readMap, int readChar);
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	bool realTimeLogic();
	CharacterData getPlayerData();
	int getCoins();
	bool getShouldRun();
	void decrementPauseTime();
};