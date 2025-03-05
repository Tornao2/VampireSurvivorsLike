#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Display {
	std::string windowTitle;
	unsigned int windowWidth, windowHeight;
	sf::RenderWindow window;
public:
	void setTitle(std::string title);
	void setResolution(unsigned int width, unsigned int height);
	void activateWindow();
	sf::RenderWindow* getWindow();
};