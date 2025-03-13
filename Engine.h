#pragma once
#include "Display.h"
#include "MainMenu.h"
#include "Settings.h"

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