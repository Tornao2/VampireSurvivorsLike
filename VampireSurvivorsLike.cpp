#include "Engine.h"

int main()
{
    Engine engine;
    sf::Texture* mainMenuTexture = engine.getSpriteHandler()->loadTexture({ 320, 320 }, "MainMenu");
    if (!mainMenuTexture) {
        return -1;
    }
    std::vector<sf::Sprite> mainMenuSprites;
    for (int y = 0; y < 4; y++) {
        mainMenuSprites.emplace_back(engine.getSpriteHandler()->loadSprite(*mainMenuTexture, { 320, 80 }, { 0, y * 80 }));
        mainMenuSprites[y].setPosition({ 240, y * 120.0f + 40 });
    }
    while (engine.getDisplay()->getWindow()->isOpen())
    {
        while (std::optional event = engine.getDisplay()->getWindow()->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                engine.getDisplay()->getWindow()->close();
        }
        engine.getDisplay()->getWindow()->clear();
        for (int i = 0; i < 4; i++) {
            engine.getDisplay()->getWindow()->draw(mainMenuSprites[i]);
        }
        engine.getDisplay()->getWindow()->display();
    }
}