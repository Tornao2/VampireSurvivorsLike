#pragma once
#include "ObjectsHandler.h"
#include "Display.h"
#include <SFML/Audio.hpp>

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
};

class Scene {
protected:
	ObjectsHandler* objectsHandler;
	SceneLabels* sceneLabel;
	sf::SoundBuffer* soundBuffer;
	int* soundVolume;
public:
	Scene(ObjectsHandler* readObjectsHandler, SceneLabels* readLabel, sf::SoundBuffer* buffer, int* volume) :objectsHandler(readObjectsHandler), sceneLabel(readLabel), soundBuffer(buffer), soundVolume(volume) {};
	virtual bool eventLogic(std::optional<sf::Event> gameEvent) = 0;
	virtual bool init() = 0;
	virtual void cleanUp() = 0;
};