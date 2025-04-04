 #include "Display.h"

Display::Display() {
	windowInstance.create(sf::VideoMode({ 0, 0 }), "", sf::Style::Titlebar | sf::Style::Close);
	windowWidth = 1440;
	windowHeight = 900;
	fullscreenMode = windowed;
	loadFromFile();
	setResolution(windowWidth, windowHeight);
	windowInstance.setTitle("PGK2 projekt");
	windowInstance.setFramerateLimit(60);
	setFullscreen(fullscreenMode);
}

float Display::getWindowWidth() {
	return windowWidth;
}

float Display::getWindowHeight() {
	return windowHeight;
}

void Display::setResolution(float readWidth, float readHeight) {
	windowWidth = readWidth;
	windowHeight = readHeight;
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
		screenView = sf::View({(float)windowWidth / 2, (float)windowHeight / 2}, sf::Vector2f((float)sf::VideoMode::getDesktopMode().size.x, (float)sf::VideoMode::getDesktopMode().size.y));
	}
	else if (fullscreenMode == windowed) {
		windowInstance.create(sf::VideoMode({ (unsigned int) windowWidth, (unsigned int) windowHeight }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
		screenView = sf::View({ (float)windowWidth / 2, (float)windowHeight / 2 }, sf::Vector2f((float)windowWidth, (float)windowHeight));
	}
	else {
		windowInstance.create(sf::VideoMode({ (unsigned int)windowWidth, (unsigned int)windowHeight }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({ (float)windowWidth / 2, (float)windowHeight / 2 }, sf::Vector2f((float)windowWidth, (float)windowHeight));
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
		inFile >> windowWidth >> delimiter >> windowHeight >> delimiter >> fullscreenStat;
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
	outFile << windowWidth << ";" << windowHeight << ";" << (int)fullscreenMode << "\n";
	outFile.close();
}
