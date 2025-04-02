#include "ResetChoice.h"

void ResetChoice::setDisplay(Display* readDisplay) {
    display = readDisplay;
}

bool ResetChoice::logic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
            selectedButton++;
            if (selectedButton == 2) 
                selectedButton = 0;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
            selectedButton--;
            if (selectedButton == -1) 
                selectedButton = 1;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            switch (selectedButton) {
            case 0:
                *sceneLabel = SETTINGS;
                break;
            case 1:
                *sceneLabel = MAINMENU;
                display->setResolution(1440, 900);
                display->setFullscreen(windowed);
                std::remove("Upgrade.txt");
                std::remove("Display.txt");
                break;
            }
            return true;
        }
    }
    return false;
}

bool ResetChoice::init() {
    selectedButton = 0;
    sf::Texture* resetTexture = objectsHandler->loadTexture({ 120, 50 }, "ResetChoice");
    if (!resetTexture) 
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadTextIntoHolder("Are you sure you want to reset?", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Are you sure you want to reset?", 42)) / 2, 0 });
    objectsHandler->getTextPointer(0)->setFillColor(DARKRED);
    objectsHandler->loadTextIntoHolder("No", 42, { (SCENEWIDTH - objectsHandler->calculateTextWidth("No", 42)) / 4 - 10.0f, 126 });
    objectsHandler->loadTextIntoHolder("Yes", 42, { 3*(SCENEWIDTH - objectsHandler->calculateTextWidth("Yes", 42)) / 4 + 10.0f, 126 });
    for (int i = 0; i < 2; i++) {
        objectsHandler->loadSpriteIntoHolder(*resetTexture, { 120,50 }, { 0, 0 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 48 + 216.0f * i, 130 });
    }
    refreshSelection();
    return false;
}

void ResetChoice::cleanUp() {   
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
}

void ResetChoice::refreshSelection() {
    for (int i = 1; i < 3; i++) 
        objectsHandler->getTextPointer(i)->setFillColor(sf::Color::White);
    for (int i = 0; i < 2; i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex, i)->setColor(sf::Color::White);
    objectsHandler->getTextPointer(selectedButton + 1)->setFillColor(GREEN);
    objectsHandler->getSpritePointer(spriteHolderIndex,selectedButton)->setColor(GREEN);
}