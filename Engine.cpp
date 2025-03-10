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
    sf::Texture* mainMenuTexture = spriteHandler->loadTexture({ 400, 600 }, "MainMenu");
    if (!mainMenuTexture) return true;  
    for (int i = 0; i < 4; i++) {
        usedTextures.emplace_back(spriteHandler->loadSprite(*mainMenuTexture, { 400,100 }, { 0, 100 }));
        usedTextures.back().setPosition({200, 50.0f + 125.0f * i});
    }
    for (int i = 0; i < 4; i++) {
        usedTextures.emplace_back(spriteHandler->loadSprite(*mainMenuTexture, { 400, 100 }, { 0, 200 + i * 100 }));
        usedTextures.back().setPosition({ 200, 50.0f + 125.0f * i });
    }
    usedTextures.emplace_back(spriteHandler->loadSprite(*mainMenuTexture, { 400,100 }, { 0, 0 }));
    usedTextures.back().setPosition({ 200, 50. });
    return false;
}

void Engine::draw() {
    display->getWindow()->clear();
    for (sf::Sprite sprite : usedTextures)
        display->getWindow()->draw(sprite);
    display->getWindow()->display();
}

void Engine::handleEvents() {
    while (std::optional event = display->getWindow()->pollEvent()){
        if (event->is<sf::Event::Closed>()) 
            display->getWindow()->close();
    }
}