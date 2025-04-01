#pragma once
#include "Scene.h"
#include "Display.h"

class ResetChoice : public Scene {
	int selectedButton;
	int spriteHolderIndex;
	void refreshSelection();
	Display* display;
public:
	using Scene::Scene;
	void setDisplay(Display* readDisplay);
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};