#pragma once
#include "Display.h"
#include "MainMenu.h"

class Engine {
	SceneLabels sceneLabel;
	Display display;
	SpriteHandler spriteHandler;
	Scene* scene;
	void draw();
	void handleEvents();
public:
	Engine();
	int mainLoop();
};