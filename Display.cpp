 #include "Display.h"

Display::Display() {
	window.create(sf::VideoMode({ 0, 0 }), "", sf::Style::Titlebar | sf::Style::Close);
	windowWidth = 1440;
	windowHeight = 900;
	fullscreen = windowed;
	loadFromFile();
	setResolution(windowWidth, windowHeight);
	window.setTitle("PGK2 projekt");
	window.setFramerateLimit(60);
	setFullscreen(fullscreen);
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
	recalibrate();
}

sf::RenderWindow* Display::getWindow() {
	return &window;
}

void Display::setFullscreen(DisplayMode ifFullscreen) {
	fullscreen = ifFullscreen;
	recalibrate();	
}

void Display::recalibrate() {
	window.clear();
	if (fullscreen == borders) {
		window.create(sf::VideoMode({ sf::VideoMode::getDesktopMode().size.x, sf::VideoMode::getDesktopMode().size.y }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({(float)windowWidth / 2, (float)windowHeight / 2}, sf::Vector2f((float)sf::VideoMode::getDesktopMode().size.x, (float)sf::VideoMode::getDesktopMode().size.y));
	}
	else if (fullscreen == windowed) {
		window.create(sf::VideoMode({ (unsigned int) windowWidth, (unsigned int) windowHeight }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
		screenView = sf::View({ (float)windowWidth / 2, (float)windowHeight / 2 }, sf::Vector2f((float)windowWidth, (float)windowHeight));
	}
	else {
		window.create(sf::VideoMode({ (unsigned int)windowWidth, (unsigned int)windowHeight }), "PGK2 projekt", sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({ (float)windowWidth / 2, (float)windowHeight / 2 }, sf::Vector2f((float)windowWidth, (float)windowHeight));
	}
	window.setView(screenView);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
}

DisplayMode Display::getFullscreen(){
	return fullscreen;
}

void Display::loadFromFile() {
	std::ifstream inFile("Resources/Display.txt");
	if (inFile) {
		char delimiter;
		std::string fullscreenStat;
		inFile >> windowWidth >> delimiter >> windowHeight >> delimiter >> fullscreenStat;
		if (std::stoi(fullscreenStat) == 0) 
			fullscreen = windowed;
		else if (std::stoi(fullscreenStat) == 1) 
			fullscreen = full;
		else 
			fullscreen = borders;
		inFile.close();
	}
}

void Display::saveToFile() {
	std::ofstream outFile("Resources/Display.txt");
	outFile << windowWidth << ";" << windowHeight << ";" << (int)fullscreen << "\n";
	outFile.close();
}
