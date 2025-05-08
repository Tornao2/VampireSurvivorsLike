#pragma once
#include "Scene.h"

class GalleryScene: public Scene {
	int spriteHolderIndex, additionalHolderIndex;
	int selectedRow;
	void refreshSelection();
	void showSprites();
public:
	using Scene::Scene;
	bool eventLogic(std::optional<sf::Event> gameEvent);
	bool init();
	void cleanUp();
};