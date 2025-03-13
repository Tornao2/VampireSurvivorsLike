#pragma once
#include "Display.h"
#include "MainMenu.h"
#include "Settings.h"

//1728/1080 1440:900 1280/800 resolutions

class Engine {
	SceneLabels sceneLabel;
	Display display;
	SpriteHandler spriteHandler;
	Scene* scene;
	void draw();
	void handleEvents();
	void changeScene();
public:
	Engine();
	int mainLoop();
};