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
    for (ListOrVector var : **spriteHandler.getSpriteHolder()) {
        Display* dispCopy = &display;
        std::visit([dispCopy](auto* container) {
            for (sf::Sprite& sprite : *container)
                dispCopy->getWindow()->draw(sprite);
            }, var);
    }
    display.getWindow()->display();
}

void Engine::handleEvents() {
    SceneLabels temp = sceneLabel;
    while (std::optional event = display.getWindow()->pollEvent()){
        bool finished = scene->logic(event);
        if (finished) {
            if (temp != sceneLabel) {
                scene->cleanUp();
            } else 
                display.getWindow()->close();
            break;
        };
    }
}