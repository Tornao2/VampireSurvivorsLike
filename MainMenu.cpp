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
    sf::Texture* mainMenuTexture = spriteHandler->loadTexture({ 200, 300 }, "MainMenu");
    if (!mainMenuTexture) return true;
    spriteHolderIndex = spriteHandler->addVectorToSpriteHolder();
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 50 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({116, 25.0f + 60.0f * i});
    }
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 100 + i * 50 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 25.0f + 60.0f * i });
    }
    spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 0 }, spriteHolderIndex);
    spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 25. });
    return false;
}

void MainMenu::cleanUp() {
    spriteHandler->clearSpriteHolder();
}

void MainMenu::refreshSelection() {
    spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116.0f, 25.0f + 60.0f * selectedButton });
}