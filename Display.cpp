 #include "Display.h"

Display::Display() {
	screenWidth = sf::VideoMode::getDesktopMode().size.x;
	screenHeight = sf::VideoMode::getDesktopMode().size.y;
	window.create(sf::VideoMode({ 0, 0 }), "", sf::Style::Titlebar | sf::Style::Close);
	windowWidth = 1440;
	windowHeight = 900;
	fullscreen = windowed;
	loadFromFile();
	setResolution(windowWidth, windowHeight);
	setTitle("PGK2 projekt");
	setFramerate(60);
	setFullscreen(fullscreen);
}

void Display::setTitle(std::string title) {
	windowTitle = title;
	window.setTitle(title);
}

unsigned int Display::getWindowWidth() {
	return windowWidth;
}

unsigned int Display::getWindowHeight() {
	return windowHeight;
}

void Display::setResolution(unsigned int width, unsigned int height) {
	windowWidth = width;
	windowHeight = height;
	recalibrate();
}

sf::RenderWindow* Display::getWindow() {
	return &window;
}

void Display::setFramerate(unsigned int readFramerate) {
	framerate = readFramerate;
	window.setFramerateLimit(framerate);
}

void Display::setFullscreen(DisplayMode ifFullscreen) {
	fullscreen = ifFullscreen;
	recalibrate();	
}

void Display::recalibrate() {
	window.clear();
	if (fullscreen == borders) {
		window.create(sf::VideoMode({ screenWidth, screenHeight }), windowTitle, sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({(float)windowWidth / 2, (float)windowHeight / 2}, sf::Vector2f((float)screenWidth, (float)screenHeight));
	}
	else if (fullscreen == windowed) {
		window.create(sf::VideoMode({ windowWidth, windowHeight }), windowTitle, sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
		screenView = sf::View({ (float)windowWidth / 2, (float)windowHeight / 2 }, sf::Vector2f((float)windowWidth, (float)windowHeight));
	}
	else {
		window.create(sf::VideoMode({ windowWidth, windowHeight }), windowTitle, sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
		screenView = sf::View({ (float)windowWidth / 2, (float)windowHeight / 2 }, sf::Vector2f((float)windowWidth, (float)windowHeight));
	}
	window.setView(screenView);
	window.setFramerateLimit(framerate);
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
		if (std::stoi(fullscreenStat) == 0) {
			fullscreen = windowed;
		}
		else if (std::stoi(fullscreenStat) == 1) {
			fullscreen = full;
		}
		else {
			fullscreen = borders;
		}
		inFile.close();
	}
}

void Display::saveToFile() {
	std::ofstream outFile("Resources/Display.txt");
	outFile << windowWidth << ";" << windowHeight << ";" << (int)fullscreen << "\n";
	outFile.close();
}

sf::View* Display::getScreenView() {
	return &screenView;
}

void Display::refreshScreenView() {
	window.setView(screenView);
}