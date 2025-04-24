#pragma once
#include "MainMenu.h"
#include "Settings.h"
#include "ResetChoice.h"
#include "UpgradeScene.h"
#include "PlayChoice.h"
#include "PlaySpace.h"
#include "FinishScreen.h"

class Engine {
	SceneLabels sceneLabel;
	Display display;
	ObjectsHandler objectsHandler;
	Scene* scene = nullptr;
	SoundManager soundManager;
	int soundVolume = 100;
	void loadVolume();
	void draw();
	void handleEvents();
	void changeScene();
	void drawPlayScene(sf::RenderTexture* texture);
	int errorCode = 0;
	int selectedMap = 0, selectedChar = 0, tempVariable = 0;
public:
	Engine();
	void mainLoop();
	int getErrorCode();
};