#pragma once
#include "ObjectsHandler.h"
#include "Display.h"
#include "SoundManager.h"

#define RED { 200, 10, 10}
#define GREEN { 40, 210, 40 }
#define BLUE { 50, 90, 250 }

enum SceneLabels {
	MAINMENU = 1,
	SETTINGS,
	RESETCHOICE,
	UPGRADE,
	PLAYCHOICE,
	PLAYSPACE,
	FINISHSCREEN,
	GALLERY
};

class Scene {
protected:
	ObjectsHandler* objectsHandler;
	SceneLabels* sceneLabel;
	SoundManager* soundManager;
	int* soundVolume;
public:
	Scene(ObjectsHandler* readObjectsHandler, SceneLabels* readLabel, SoundManager* readManager, int* volume) :objectsHandler(readObjectsHandler), sceneLabel(readLabel), soundManager(readManager), soundVolume(volume) {};
	virtual bool eventLogic(std::optional<sf::Event> gameEvent) = 0;
	virtual bool init() = 0;
	virtual void cleanUp() = 0;
};