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
    sf::RenderTexture renderTexture({ 432, 270 });
    renderTexture.clear();
    for (ListOrVector var : **spriteHandler.getSpriteHolder()) {
        std::visit([&renderTexture](auto* container) {
            for (sf::Sprite& sprite : *container)
                renderTexture.draw(sprite);
            }, var);
    }
    renderTexture.display();
    sf::Sprite finalSprite(renderTexture.getTexture());
    finalSprite.setScale({display.getWindow()->getSize().x/ 432.0f,display.getWindow()->getSize().y/ 270.f });
    display.getWindow()->draw(finalSprite);
    display.getWindow()->display();
}

void Engine::handleEvents() {
    SceneLabels temp = sceneLabel;
    if (display.getWindow()->hasFocus()) {
        while (std::optional event = display.getWindow()->pollEvent()) {
            bool finished = scene->logic(event);
            if (finished) {
                if (temp != sceneLabel) {
                    scene->cleanUp();
                    delete scene;
                    changeScene();
                }
                else
                    display.getWindow()->close();
                break;
            };
        }
    }
}

void Engine::changeScene() {
    switch (sceneLabel) {
    case MAINMENU:
        scene = new MainMenu(&spriteHandler, &sceneLabel);
        break;
    case SETTINGS:
        scene = new SettingsScene(&spriteHandler, &sceneLabel);
        break;
    }
    scene->init();
}