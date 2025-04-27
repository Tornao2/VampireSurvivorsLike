#pragma once
#include "Scene.h"

class SettingsScene : public Scene {
	int spriteHolderIndex;
	int selectedRow, selectedColumn;
	Display* display;
	sf::Music* playedMusic;
	void refreshSelection();
public:
	using Scene::Scene;
	void setDisplay(Display* readDisplay);
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
	void saveVolume();
	void setMusicPointer(sf::Music* readMusic);
};