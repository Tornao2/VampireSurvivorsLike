#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

constexpr short int SCENEWIDTH = 432;
constexpr short int SCENEHEIGHT = 270;

enum DisplayMode {
	windowed,
	full,
	borders
};

class Display {
	float windowWidth, windowHeight;
	DisplayMode fullscreen;
	sf::View screenView;
	sf::RenderWindow window;
	void recalibrate();
public:
	Display();
	void setResolution(float readWidth, float readHeight);
	sf::RenderWindow* getWindow();
	void setFullscreen(DisplayMode ifFullscreen);
	float getWindowWidth();
	float getWindowHeight();
	DisplayMode getFullscreen();
	void loadFromFile();
	void saveToFile();
};