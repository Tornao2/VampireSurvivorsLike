#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#define SCENEWIDTH 432
#define SCENEHEIGHT 270

enum DisplayMode {
	windowed,
	full,
	borders
};

class Display {
	float windowWidth, windowHeight;
	DisplayMode fullscreenMode;
	sf::View screenView;
	sf::RenderWindow windowInstance;
	void recalibrateWindow();
public:
	Display();
	void setResolution(float readWidth, float readHeight);
	sf::RenderWindow* getWindow();
	void setFullscreen(DisplayMode readFullscreenMode);
	float getWindowWidth();
	float getWindowHeight();
	DisplayMode getFullscreen();
	void loadFromFile();
	void saveToFile();
};