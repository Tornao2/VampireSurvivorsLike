#include "FinishScreen.h"

bool FinishScreen::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>())
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            soundManager->playSound("menuSelect");
            *sceneLabel = MAINMENU;
            return true;
        }
    }
    return false;
}

void FinishScreen::setCoins(int readCoins, int chosenMap, int chosenChar) {
    coins = readCoins;
    Modifiers modifManager;
    modifManager.loadModifiersFromFile();
    modifManager.changeCoins(coins);
    modifManager.saveModifiersToFile();
    if (readCoins >= 600) {
        Unlocks unlockedManager;
        std::vector<bool> unlockedChars = unlockedManager.loadUnlocked("CharactersUnlocked");
        std::vector<bool> unlockedMaps = unlockedManager.loadUnlocked("MapsUnlocked");
        if (chosenMap < unlockedMaps.size() - 1) {
            if (!unlockedMaps.at(chosenMap + 1)) {
                unlocked = true;
                unlockedMaps.at(chosenMap + 1) = true;
                unlockedManager.saveUnlocked(unlockedMaps, "MapsUnlocked");
            }
        }
        if (chosenChar < unlockedChars.size() - 1) {
            if (!unlockedChars.at(chosenChar + 1)) {
                unlocked = true;
                unlockedChars.at(chosenChar + 1) = true;
                unlockedManager.saveUnlocked(unlockedChars, "CharactersUnlocked");
            }
        }
    }
}

bool FinishScreen::init() {
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonTexture)
        return true;
    objectsHandler->loadTextIntoHolder("Coins you have earned:", 27, {(SCENEWIDTH - (objectsHandler->calculateTextWidth("Coins you have earned:", 27))) / 2, 0});
    objectsHandler->loadTextIntoHolder(std::to_string(coins), 35, { (SCENEWIDTH - (objectsHandler->calculateTextWidth(std::to_string(coins), 35))) / 2, 50 });
    if (unlocked) 
        objectsHandler->loadTextIntoHolder("You have unlocked something new!", 27, { (SCENEWIDTH - (objectsHandler->calculateTextWidth("You have unlocked something new!", 27))) / 2, 100 });
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 200 });
    objectsHandler->loadTextIntoHolder("Menu", 27, { (SCENEWIDTH - (objectsHandler->calculateTextWidth("Menu", 27))) / 2, 200 });
    objectsHandler->getTextPointer(-1)->setFillColor(GREEN);
    return false;
}

void FinishScreen::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
}

void FinishScreen::refreshSelection() {
    return;
}