#include "MainMenu.h"

bool MainMenu::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()){
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
            selectedButton++;
            if (selectedButton == 5) 
                selectedButton = 0;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
            selectedButton--;
            if (selectedButton == -1) 
                selectedButton = 4;
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
                    *sceneLabel = GALLERY;
                    break;
                case 3:
                    *sceneLabel = SETTINGS;
                    break; 
                case 4:
                    break;
            }
            return true;
        }
    }
    return false;
}

bool MainMenu::init() {
    selectedButton = 0;
    sf::Texture* mainMenuTexture = objectsHandler->loadTexture({ 432, 270 }, "MainMenuBG");
    if (!mainMenuTexture) 
        return true;
    objectsHandler->loadTextIntoHolder("Play", 27, { 352 - (objectsHandler->calculateTextWidth("Play", 27))/2, 34 });
    objectsHandler->loadTextIntoHolder("Upgrade", 27, { 352 - (objectsHandler->calculateTextWidth("Upgrade", 27)) / 2, 79 });
    objectsHandler->loadTextIntoHolder("Gallery", 27, { 352 - (objectsHandler->calculateTextWidth("Gallery", 27)) / 2, 124 });
    objectsHandler->loadTextIntoHolder("Settings", 27, { 352 - (objectsHandler->calculateTextWidth("Settings", 27)) / 2, 169 });
    objectsHandler->loadTextIntoHolder("Exit", 27, { 352 - (objectsHandler->calculateTextWidth("Exit", 27)) / 2, 214 });
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*mainMenuTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 76 }, "ButtonSprites");
    if (!buttonTexture)
        return true;
    for (int i = 0; i < 5; i++) {
        objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 310, 45.0f * i+35 });
    }
    refreshSelection();
    return false;
}

void MainMenu::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
}

void MainMenu::refreshSelection() {
    for (sf::Text& text : *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    objectsHandler->getTextPointer(selectedButton)->setFillColor(GREEN);
}