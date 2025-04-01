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
	Scene* scene;
	void draw();
	void handleEvents();
	void changeScene();
	int errorCode;
	int selectedMap, selectedChar;
public:
	Engine();
	void mainLoop();
	int getErrorCode();
};