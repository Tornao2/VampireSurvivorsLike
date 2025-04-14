#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#define SCENEWIDTH 432
#define SCENEHEIGHT 270
static char breakCharacter = ';';

enum DisplayMode {
	windowed,
	full,
	borders
};

class Display {
	sf::Vector2f windowSize;
	DisplayMode fullscreenMode;
	sf::View screenView;
	sf::RenderWindow windowInstance;
	void recalibrateWindow();
public:
	Display();
	void setResolution(sf::Vector2f readResolution);
	sf::RenderWindow* getWindow();
	void setFullscreen(DisplayMode readFullscreenMode);
	sf::Vector2f getWindowSize();
	DisplayMode getFullscreen();
	void loadFromFile();
	void saveToFile();
};