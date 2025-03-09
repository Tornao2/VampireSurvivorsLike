#pragma once
#include "Display.h"
#include "SpriteHandler.h"

class Engine {
	Display* display;
	SpriteHandler* spriteHandler;
public:
	Engine();
	Display* getDisplay();
	SpriteHandler* getSpriteHandler();
};