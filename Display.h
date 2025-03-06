#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Display {
	std::string windowTitle;
	unsigned int framerate, windowWidth, windowHeight;
	bool fullscreen;
	sf::RenderWindow window;
public:
	Display();
	void turnOffCursor();
	void setTitle(std::string title);
	void setResolution(unsigned int width, unsigned int height);
	void setFramerate(unsigned int readFramerate);
	sf::RenderWindow* getWindow();
	void setFullscreen(bool ifFullscreen);
};