#pragma once
#include "Scene.h"

class ResetChoice : public Scene {
	int selectedButton;
	int spriteHolderIndex;
	Display* display;
	void refreshSelection();
public:
	using Scene::Scene;
	void setDisplay(Display* readDisplay);
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};