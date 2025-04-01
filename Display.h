#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

enum DisplayMode {
	windowed,
	full,
	borders
};

class Display {
	std::string windowTitle;
	unsigned int framerate, windowWidth, windowHeight, screenWidth, screenHeight;
	DisplayMode fullscreen;
	sf::View screenView;
	sf::RenderWindow window;
	void recalibrate();
public:
	Display();
	void setTitle(std::string title);
	void setResolution(unsigned int width, unsigned int height);
	void setFramerate(unsigned int readFramerate);
	sf::RenderWindow* getWindow();
	void setFullscreen(DisplayMode ifFullscreen);
	unsigned int getWindowWidth();
	unsigned int getWindowHeight();
	DisplayMode getFullscreen();
	void loadFromFile();
	void saveToFile();
	sf::View* getScreenView();
	void refreshScreenView();
};