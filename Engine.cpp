#include "Engine.h"

Engine::Engine() {
	display = new Display();	
	spriteHandler = new SpriteHandler();
}

Display* Engine::getDisplay() {
	return display;
}

SpriteHandler* Engine::getSpriteHandler() {
	return spriteHandler;
}