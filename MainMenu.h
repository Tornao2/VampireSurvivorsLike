#pragma once
#include "Scene.h"

class MainMenu : public Scene {
	std::vector<sf::Sprite>* spriteHolder;
public:
	using Scene::Scene;
	bool logic();
	bool init();
};