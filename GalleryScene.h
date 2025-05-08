#pragma once
#include "Scene.h"

class GalleryScene: public Scene {
	int spriteHolderIndex;
	int selectedRow;
	void refreshSelection();
public:
	using Scene::Scene;
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};