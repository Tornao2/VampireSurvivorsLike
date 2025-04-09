#pragma once
#include "ObjectsHandler.h"
#include "Display.h"

#define DARKRED { 190, 0, 0}
#define GREEN { 0, 130, 0 }
#define BLUE { 100, 80, 200 }

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