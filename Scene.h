#pragma once
#include "ObjectsHandler.h"
#include "Display.h"

constexpr sf::Color DARKRED = { 150, 0, 0};
constexpr sf::Color GREEN = { 0, 120, 0 };
constexpr sf::Color BLUE = { 70, 60, 180 };

enum SceneLabels {
	MAINMENU = 1,
	SETTINGS,
	RESETCHOICE,
	UPGRADE,
	PLAYCHOICE,
	GALLERY,
	PLAYSPACE
};

class Scene {
protected:
	ObjectsHandler* objectsHandler;
	SceneLabels* sceneLabel;
public:
	Scene(ObjectsHandler* readObjectsHandler, SceneLabels* readLabel) :objectsHandler(readObjectsHandler), sceneLabel(readLabel) {};
	virtual bool logic(std::optional<sf::Event> gameEvent) = 0;
	virtual bool init() = 0;
	virtual void cleanUp() = 0;
};