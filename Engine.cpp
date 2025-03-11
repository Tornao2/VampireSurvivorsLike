#include "Engine.h"

Engine::Engine() {
	sceneLabel = MAINMENU;
    scene = nullptr;
}

int Engine::mainLoop() {
    scene = new MainMenu(&spriteHandler, &sceneLabel);
    if ((scene->init())) 
        return -1;
    while (display.getWindow()->isOpen())
    {
        handleEvents();
        draw();
    }
}

void Engine::draw() {
    display.getWindow()->clear();
    for (std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*> var : spriteHandler.getSpriteHolder()) {
        Display* dispCopy = &display;
        std::visit([dispCopy](auto* container) {
            for (sf::Sprite& sprite : *container)
                dispCopy->getWindow()->draw(sprite);
            }, var);
    }
    display.getWindow()->display();
}

void Engine::handleEvents() {
    while (std::optional event = display.getWindow()->pollEvent()){
        if (event->is<sf::Event::Closed>()) 
            display.getWindow()->close();
    }
}