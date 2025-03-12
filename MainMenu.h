#pragma once
#include "Scene.h"

class MainMenu : public Scene {
	int spriteHolderIndex;
public:
	using Scene::Scene;
	bool logic();
	bool init();
};