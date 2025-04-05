 #include "Display.h"

Display::Display() {
	windowInstance.create(sf::VideoMode({ 0, 0 }), "", sf::Style::Titlebar | sf::Style::Close);
	windowSize = { 1440, 900 };
	fullscreenMode = windowed;
	loadFromFile();
	setResolution(windowSize);
	windowInstance.setTitle("PGK2 projekt");
	windowInstance.setFramerateLimit(60);
	setFullscreen(fullscreenMode);
}

sf::Vector2f Display::getWindowSize() {
	return windowSize;
}

void Display::setResolution(sf::Vector2f readResolution) {
	windowSize = readResolution;
	recalibrateWindow();
}

sf::RenderWindow* Display::getWindow() {
	return &windowInstance;
}

void Display::setFullscreen(DisplayMode readFullscreenMode) {
	fullscreenMode = readFullscreenMode;
	recalibrateWindow();
}

void Display::recalibrateWindow() {
	windowInstance.clear();
	if (fullscreenMode == borders) {
		windowInstance.create(sf::VideoMode({ sf::VideoMode::getDesktopMode().size.x, sf::VideoMode::getDesktopMode().size.y }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({windowSize.x / 2, windowSize.y / 2}, sf::Vector2f((float)sf::VideoMode::getDesktopMode().size.x, (float)sf::VideoMode::getDesktopMode().size.y));
	}
	else if (fullscreenMode == windowed) {
		windowInstance.create(sf::VideoMode({ (unsigned int) windowSize.x, (unsigned int) windowSize.y}), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
		screenView = sf::View({windowSize.x / 2,windowSize.y / 2 }, windowSize);
	}
	else {
		windowInstance.create(sf::VideoMode({ (unsigned int)windowSize.x, (unsigned int)windowSize.y }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({ windowSize.x / 2,windowSize.y / 2 }, windowSize);
	}
	windowInstance.setView(screenView);
	windowInstance.setFramerateLimit(60);
	windowInstance.setMouseCursorVisible(false);
}

DisplayMode Display::getFullscreen(){
	return fullscreenMode;
}

void Display::loadFromFile() {
	std::ifstream inFile("Resources/Display.txt");
	if (inFile) {
		char delimiter;
		std::string fullscreenStat;
		inFile >> windowSize.x >> delimiter >> windowSize.y >> delimiter >> fullscreenStat;
		if (std::stoi(fullscreenStat) == 0) 
			fullscreenMode = windowed;
		else if (std::stoi(fullscreenStat) == 1) 
			fullscreenMode = full;
		else 
			fullscreenMode = borders;
		inFile.close();
	}
}

void Display::saveToFile() {
	std::ofstream outFile("Resources/Display.txt");
	outFile << windowSize.x << ";" << windowSize.y << ";" << (int)fullscreenMode << "\n";
	outFile.close();
}
