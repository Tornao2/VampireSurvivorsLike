#include "Display.h"

void Display::setTitle(std::string title) {
	windowTitle = title;
}

void Display::setResolution(unsigned int width, unsigned int height) {
	windowHeight = height;
	windowWidth = width;
}

void Display::activateWindow() {
	window.create(sf::VideoMode({ windowWidth, windowHeight }), windowTitle);
}

sf::RenderWindow* Display::getWindow() {
	return &window;
}