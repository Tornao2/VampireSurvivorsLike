#pragma once
#include "Scene.h"

class MainMenu : public Scene {
	int spriteHolderIndex;
	int selectedButton;
public:
	using Scene::Scene;
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};