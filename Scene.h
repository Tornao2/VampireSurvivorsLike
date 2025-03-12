#pragma once
#include "SpriteHandler.h"

enum SceneLabels {
	MAINMENU
};

class Scene {
protected:
	SpriteHandler* spriteHandler;
	SceneLabels* sceneLabel;
public:
	Scene(SpriteHandler* a, SceneLabels* b) :spriteHandler(a), sceneLabel(b) {};
	virtual bool logic(std::optional<sf::Event> gameEvent) = 0;
	virtual bool init() = 0;
	virtual void cleanUp() = 0;
};