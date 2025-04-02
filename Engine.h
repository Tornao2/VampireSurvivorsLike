#pragma once
#include "MainMenu.h"
#include "Settings.h"
#include "ResetChoice.h"
#include "UpgradeScene.h"
#include "PlayChoice.h"
#include "PlaySpace.h"

class Engine {
	SceneLabels sceneLabel;
	Display display;
	ObjectsHandler objectsHandler;
	Scene* scene = nullptr;
	void draw();
	void handleEvents();
	void changeScene();
	int errorCode = 0;
	int selectedMap = 0, selectedChar = 0;
public:
	Engine();
	void mainLoop();
	int getErrorCode();
};