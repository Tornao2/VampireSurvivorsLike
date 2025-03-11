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
	virtual bool logic() = 0;
	virtual bool init() = 0;
};