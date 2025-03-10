#include "Engine.h"

Engine::Engine() {
	sceneLabel = MAINMENU;
	display = new Display();	
	spriteHandler = new SpriteHandler();
}

int Engine::mainLoop() {
    if (initMainMenu()) 
        return -1;
    while (display->getWindow()->isOpen())
    {
        handleEvents();
        draw();
    }
}

bool Engine::initMainMenu() {
    sf::Texture* mainMenuTexture = spriteHandler->loadTexture({ 320, 320 }, "MainMenu");
    if (!mainMenuTexture) return true;
    for (int y = 0; y < 4; y++) {
        usedTextures.emplace_back(spriteHandler->loadSprite(*mainMenuTexture, { 320, 80 }, { 0, y * 80 }));
        usedTextures[y].setPosition({ 240, y * 120.0f + 40 });
    }
    return false;
}

void Engine::draw() {
    display->getWindow()->clear();
    for (sf::Sprite sprite : usedTextures) 
        display->getWindow()->draw(sprite);
    display->getWindow()->display();
}

void Engine::handleEvents() {
    while (std::optional event = display->getWindow()->pollEvent())
    {
        if (event->is<sf::Event::Closed>()) 
            display->getWindow()->close();
    }
}