#pragma once
#include "ObjectsHandler.h"
#include "Display.h"

#define DARKRED { 150, 0, 0}
#define GREEN { 0, 120, 0 }
#define BLUE { 70, 60, 180 }

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
	virtual bool eventLogic(std::optional<sf::Event> gameEvent) = 0;
	virtual bool init() = 0;
	virtual void cleanUp() = 0;
};