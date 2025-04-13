#pragma once
#include "ObjectsHandler.h"
#include "Display.h"

#define DARKRED { 200, 10, 10}
#define GREEN { 40, 210, 40 }
#define BLUE { 50, 90, 250 }

enum SceneLabels {
	MAINMENU = 1,
	SETTINGS,
	RESETCHOICE,
	UPGRADE,
	PLAYCHOICE,
	GALLERY,
	PLAYSPACE,
	FINISHSCREEN
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