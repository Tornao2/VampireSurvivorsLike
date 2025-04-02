#include "MainMenu.h"

bool MainMenu::logic(std::optional<sf::Event> gameEvent) {
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
    sf::Texture* mainMenuTexture = objectsHandler->loadTexture({ 200, 120 }, "MainMenu");
    if (!mainMenuTexture) 
        return true;
    objectsHandler->loadTextIntoHolder("Start", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Start", 42))/2, -2});
    objectsHandler->loadTextIntoHolder("Upgrades", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Upgrades", 42)) / 2, 52 });
    objectsHandler->loadTextIntoHolder("Gallery", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Gallery", 42)) / 2, 106 });
    objectsHandler->loadTextIntoHolder("Settings", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Settings", 42)) / 2, 160 });
    objectsHandler->loadTextIntoHolder("Exit", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Exit", 42)) / 2, 214 });
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    for (int i = 0; i < 5; i++) {
        objectsHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 50 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({116, 2.0f + 54 * i});
    }
    objectsHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 2.0f });
    return false;
}

void MainMenu::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
}

void MainMenu::refreshSelection() {
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 2.0f + 54 * selectedButton });
    for (sf::Text& text : *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    objectsHandler->getTextPointer(selectedButton)->setFillColor(GREEN);
}