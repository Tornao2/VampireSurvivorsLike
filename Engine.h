#pragma once
#include "Display.h"
#include "SpriteHandler.h"

enum SceneLabels {
	MAINMENU
};

class Engine {
	SceneLabels sceneLabel;
	Display* display;
	SpriteHandler* spriteHandler;
	std::vector<sf::Sprite> usedTextures;
	bool initMainMenu();
	void draw();
public:
	Engine();
	int mainLoop();
	void handleEvents();
};