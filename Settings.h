#pragma once
#include "Scene.h"
#include "Display.h"

class SettingsScene : public Scene {
	int spriteHolderIndex;
	void refreshSelection();
	int selectedRow, selectedColumn;
	Display* display;
public:
	using Scene::Scene;
	void setDisplay(Display* readDisplay);
	bool logic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};