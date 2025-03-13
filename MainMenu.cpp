#include "MainMenu.h"

bool MainMenu::logic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) {
        return true;
    } else if (gameEvent->is<sf::Event::KeyPressed>()){
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
            selectedButton++;
            if (selectedButton == 4)
                selectedButton = 0;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
            selectedButton--;
            if (selectedButton == -1)
                selectedButton = 3;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            switch (selectedButton) {
            case 0:
                *sceneLabel = PLAYCHOICE;
                break;
            case 1:
                *sceneLabel = UPGRADE;
                break; 
            case 2:
                *sceneLabel = SETTINGS;
                break; 
            case 3:
                break;
            }
            return true;
        }
    }
    return false;
}

bool MainMenu::init() {
    selectedButton = 0;
    sf::Texture* mainMenuTexture = spriteHandler->loadTexture({ 400, 600 }, "MainMenu");
    if (!mainMenuTexture) return true;
    spriteHolderIndex = spriteHandler->addVectorToSpriteHolder();
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 400,100 }, { 0, 100 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({200, 50.0f + 125.0f * i});
    }
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 400,100 }, { 0, 200 + i * 100 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 200, 50.0f + 125.0f * i });
    }
    spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 400,100 }, { 0, 0 }, spriteHolderIndex);
    spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 200, 50. });
    return false;
}

void MainMenu::cleanUp() {
    spriteHandler->clearSpriteHolder();
}

void MainMenu::refreshSelection() {
    spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 200.0f, 50.0f + 125.0f * selectedButton });
}