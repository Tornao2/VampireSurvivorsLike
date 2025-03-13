#pragma once
#include "Scene.h"

class SettingsScene : public Scene {
	int spriteHolderIndex;
	int selectedButton;
	void refreshSelection();
public:
	using Scene::Scene;
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};