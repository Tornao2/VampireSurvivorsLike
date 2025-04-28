#pragma once
#include "MainMenu.h"
#include "Settings.h"
#include "ResetChoice.h"
#include "UpgradeScene.h"
#include "PlayChoice.h"
#include "PlaySpace.h"
#include "FinishScreen.h"

class Engine {
	SceneLabels sceneLabel = MAINMENU;
	Display display;
	ObjectsHandler objectsHandler;
	Scene* scene = nullptr;
	SoundManager soundManager;
	sf::Music playedMusic;
	int soundVolume = 100;
	void loadVolume();
	void draw();
	void handleEvents();
	void changeScene();
	void drawPlayScene(sf::RenderTexture* texture);
	void loadMusic(std::string filename);
	int errorCode = 0;
	int selectedMap = 0, selectedChar = 0, tempVariable = 0;
public:
	void mainLoop();
	int getErrorCode();
};