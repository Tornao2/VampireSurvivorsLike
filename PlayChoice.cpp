#include "PlayChoice.h"

bool PlayChoice::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
            selectedRow++;
            if (selectedRow == 4) 
                selectedRow = 0;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
            selectedRow--;
            if (selectedRow == -1) 
                selectedRow = 3;
            refreshSelection();
        } else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
            if (selectedRow == 0) {
                if (*selectedMap != NUMBEROFMAPS -1)
                    (*selectedMap)++;
            }
            else if (selectedRow == 1) {
                if (*selectedPlayer != NUMBEROFCHARS - 1)
                    (*selectedPlayer)++;
            }
            else 
                return false;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
            if (selectedRow == 0) {
                if (*selectedMap != 0)
                    (*selectedMap)--;
            }
            else if (selectedRow == 1) {
                if (*selectedPlayer != 0)
                    (*selectedPlayer)--;
            }
            else 
                return false;
            refreshSelection();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            if (selectedRow == 2) {
                if (unlockedMaps.at(*selectedMap) && unlockedChars.at(*selectedPlayer)) {
                    *sceneLabel = PLAYSPACE;
                    return true;
                }
            }
            else if (selectedRow == 3) {
                *sceneLabel = MAINMENU;
                return true;
            }
        }
    }
    return false;
}

bool PlayChoice::init() {
    *selectedMap = *selectedPlayer = selectedRow = 0;
    sf::Texture* playChoiceTexture = objectsHandler->loadTexture({ 237, 121 }, "PlaySelect");
    if (!playChoiceTexture) 
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 136,75 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 148, 1});
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 91,94 }, { 136, 27 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 170, 78.0f });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 120,45 }, { 0, 76 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 156, 174 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 120,45 }, { 0, 76 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 156, 222 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 59,27 }, { 136, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 324, 25.0f });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 59,27 }, { 136, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setScale({ -1, 1 });
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 108, 25.0f });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 59,27 }, { 136, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 324, 111 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 59,27 }, { 136, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setScale({ -1, 1 });
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 108, 111 });
    objectsHandler->loadTextIntoHolder("Start", 25, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Start", 25)) / 2, 178 });
    objectsHandler->loadTextIntoHolder("Return", 25, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Return", 25)) / 2, 226 });
    objectsHandler->addVectorToSpriteHolder();
    playChoiceTexture = objectsHandler->loadTexture({ 272, 150 }, "MapThumbnails");
    if (!playChoiceTexture) 
        return true;
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 136,75 }, { 0, 75 }, spriteHolderIndex+1);
    objectsHandler->getSpritePointer(spriteHolderIndex+1, -1)->setPosition({ 148, 1 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 136,75 }, { 0, 0 }, spriteHolderIndex+1);
    objectsHandler->getSpritePointer(spriteHolderIndex + 1, -1)->setPosition({ 148, 1 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 136,75 }, { 136, 0 }, spriteHolderIndex+1);
    objectsHandler->getSpritePointer(spriteHolderIndex + 1, -1)->setPosition({ 148, 1 });
    objectsHandler->addVectorToSpriteHolder();
    playChoiceTexture = objectsHandler->loadTexture({ 182, 188 }, "CharacterThumbnails");
    if (!playChoiceTexture) 
        return true;
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 91,94 }, { 0, 94 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 170, 78.0f });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 91,94 }, { 0, 0 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 170, 78.0f });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 91,94 }, { 91, 0 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 170, 78.0f });
    Unlocks unlocks;
    unlockedChars = unlocks.loadUnlocked("CharactersUnlocked");
    unlockedMaps = unlocks.loadUnlocked("MapsUnlocked");
    refreshSelection();
    return false;
}

void PlayChoice::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
}

void PlayChoice::setPointers(int* readMap, int* readPlayer) {
    selectedMap = readMap;
    selectedPlayer = readPlayer;
}

void PlayChoice::refreshSelection() {
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex, i)->setColor(sf::Color::White);
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex+1); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex+1, i)->setColor({255, 255, 255, 0});
    if (unlockedMaps.at(*selectedMap)) 
        objectsHandler->getSpritePointer(spriteHolderIndex + 1, *selectedMap + 1)->setColor(sf::Color::White);
    else 
        objectsHandler->getSpritePointer(spriteHolderIndex + 1, 0)->setColor(sf::Color::White);
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex + 2); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex + 2, i)->setColor({ 255, 255, 255, 0 });
    if (unlockedChars.at(*selectedPlayer)) 
        objectsHandler->getSpritePointer(spriteHolderIndex + 2, *selectedPlayer + 1)->setColor(sf::Color::White);
    else 
        objectsHandler->getSpritePointer(spriteHolderIndex + 2, 0)->setColor(sf::Color::White);
    for (sf::Text& text: *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    objectsHandler->getSpritePointer(spriteHolderIndex, selectedRow)->setColor(GREEN);
    if (selectedRow == 2 || selectedRow == 3) 
        objectsHandler->getTextPointer(selectedRow-2)->setFillColor(GREEN);
    if (*selectedMap == 0) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 5)->setColor(DARKRED);
    else if (*selectedMap == NUMBEROFMAPS - 1) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 4)->setColor(DARKRED);
    if(*selectedPlayer == 0) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 7)->setColor(DARKRED);
    else if (*selectedPlayer == NUMBEROFCHARS - 1) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 6)->setColor(DARKRED);
}