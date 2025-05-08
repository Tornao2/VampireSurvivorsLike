#include "ResetChoice.h"

void ResetChoice::setDisplay(Display* readDisplay) {
    display = readDisplay;
}

bool ResetChoice::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
            soundManager->playSound("menuChange", true);
            selectedButton++;
            if (selectedButton == 2) 
                selectedButton = 0;
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
            soundManager->playSound("menuChange", true);
            selectedButton--;
            if (selectedButton == -1) 
                selectedButton = 1;
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            soundManager->playSound("menuSelect", true);
            switch (selectedButton) {
                case 0:
                    *sceneLabel = SETTINGS;
                    break;
                case 1:
                    *sceneLabel = MAINMENU;
                    display->setResolution({ 1440, 900 });
                    display->setFullscreen(windowed);
                    std::remove("Resources/Upgrade.txt");
                    std::remove("Resources/Display.txt");
                    std::remove("Resources/CharactersUnlocked.txt");
                    std::remove("Resources/MapsUnlocked.txt");
                    std::remove("Resources/Misc.txt");
                    *soundVolume = 100;
                    break;
                }
            return true;
        }
        refreshSelection();
    }
    return false;
}

bool ResetChoice::init() {
    selectedButton = 0;
    sf::Texture* backgroundTexture = objectsHandler->loadTexture({ 432, 270 }, "ResetBG");
    if (!backgroundTexture)
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*backgroundTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonTexture)
        return true;
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 135,64 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 264, 130 });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 135,64 }, { 135, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 48, 130 });
    objectsHandler->loadTextIntoHolder("Are you sure you want to reset?", 30, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Are you sure you want to reset?", 30)) / 2, 20 });
    objectsHandler->loadTextIntoHolder("No", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("No", 36)) / 4, 136 });
    objectsHandler->loadTextIntoHolder("Yes", 36, { 3*(SCENEWIDTH - objectsHandler->calculateTextWidth("Yes", 36)) / 4 + 16, 136 });
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
    objectsHandler->getTextPointer(selectedButton + 1)->setFillColor(GREEN);
}