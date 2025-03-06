#include "Display.h"

Display::Display() {
	windowWidth = windowHeight = fullscreen = framerate = 0;
	window.create(sf::VideoMode({ 0, 0 }), "");
}

void Display::setTitle(std::string title) {
	windowTitle = title;
	window.setTitle(title);
}

void Display::setResolution(unsigned int width, unsigned int height) {
	windowWidth = width;
	windowHeight = height;
	window.setSize({ width, height });
}

void Display::turnOffCursor() {
	window.setMouseCursorVisible(false);
}

sf::RenderWindow* Display::getWindow() {
	return &window;
}

void Display::setFramerate(unsigned int readFramerate) {
	framerate = readFramerate;
	window.setFramerateLimit(framerate);
}

void Display::setFullscreen(bool ifFullscreen) {
	fullscreen = ifFullscreen;
	unsigned int screenWidth = sf::VideoMode::getDesktopMode().size.x;
	unsigned int screenHeight = sf::VideoMode::getDesktopMode().size.y;
	if (ifFullscreen) {
		float newWidth = windowWidth * (float)screenHeight / windowHeight;
		sf::View view(sf::FloatRect({ 0.0f, 0.0f }, { (float)windowWidth, (float)windowHeight }));
		window.create(sf::VideoMode({ screenWidth, screenHeight }), windowTitle, sf::State::Fullscreen);
		view.setViewport({
			{(sf::VideoMode::getDesktopMode().size.x - newWidth) / (2.0f * screenWidth), 0.0f},
			{newWidth / screenWidth, 1.0f}});
		window.setView(view);
	}
	else 
		window.create(sf::VideoMode({ windowWidth, windowHeight }), windowTitle, sf::State::Windowed);
	window.setFramerateLimit(framerate);
	window.setMouseCursorVisible(false);
}