#include "PlayChoice.h"

bool PlayChoice::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
            soundManager->playSound("menuChange");
            selectedRow++;
            if (selectedRow == 4) 
                selectedRow = 0;
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
            soundManager->playSound("menuChange");
            selectedRow--;
            if (selectedRow == -1) 
                selectedRow = 3;
        } else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
            if (selectedRow == 0 && *selectedMap != NUMBEROFMAPS - 1) {
                (*selectedMap)++;
                soundManager->playSound("menuChange");
            }
            else if (selectedRow == 0 && *selectedMap == NUMBEROFMAPS - 1)
                soundManager->playSound("menuBlock");
            else if (selectedRow == 1 && *selectedPlayer != NUMBEROFCHARS - 1) {
                (*selectedPlayer)++;
                soundManager->playSound("menuChange");
                refreshCharacterStats();
            }
            else if (selectedRow == 1 &&  *selectedPlayer == NUMBEROFCHARS - 1)
                soundManager->playSound("menuBlock");
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
            soundManager->playSound("menuChange");
            if (selectedRow == 0 && *selectedMap != 0) {
                (*selectedMap)--;
                soundManager->playSound("menuChange");
            } else if (selectedRow == 0 && *selectedMap == 0)
                soundManager->playSound("menuBlock");
            else if (selectedRow == 1 && *selectedPlayer != 0) {
                (*selectedPlayer)--;
                refreshCharacterStats();
                soundManager->playSound("menuChange");
            } else if (selectedRow == 1 &&  *selectedPlayer == 0)
                soundManager->playSound("menuBlock");
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            soundManager->playSound("menuSelect");
            if (selectedRow == 2 && unlockedMaps.at(*selectedMap) && unlockedChars.at(*selectedPlayer)){
                *sceneLabel = PLAYSPACE;
                return true;
            }
            else if (selectedRow == 3) {
                *sceneLabel = MAINMENU;
                return true;
            }
        }
        refreshSelection();
    }
    return false;
}

bool PlayChoice::init() {
    *selectedMap = *selectedPlayer = selectedRow = 0;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    sf::Texture* playChoiceTexture = objectsHandler->loadTexture({ 432, 270 }, "UpgradesBG");
    if (!playChoiceTexture)
        return true;
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
    playChoiceTexture = objectsHandler->loadTexture({ 240, 108 }, "PlayChoiceTextures");
    if (!playChoiceTexture)
        return true;
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 130,86 }, { 110, 22 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 151, 1 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 130,86 }, { 110, 22 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 151, 90 });
    sf::Texture* buttonTextures = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonTextures)
        return true;
    objectsHandler->loadSpriteIntoHolder(*buttonTextures, { 90,38 }, { 270, 38 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 180 });
    objectsHandler->loadSpriteIntoHolder(*buttonTextures, { 90,38 }, { 270, 38 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 226 });
    objectsHandler->loadTextIntoHolder("Start", 25, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Start", 25)) / 2, 183 });
    objectsHandler->loadTextIntoHolder("Return", 25, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Return", 25)) / 2, 229 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 26,22 }, { 110, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 101, 32 });
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setScale({ -1, 1 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 26,22 }, { 110, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 331, 32 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 26,22 }, { 110, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 101, 121 });
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setScale({ -1, 1 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 26,22 }, { 110, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 331, 121 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 110,104 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 290, 150 });
    objectsHandler->loadTextIntoHolder("Hp:", 12, { 303, 161 });
    objectsHandler->loadTextIntoHolder("Ms:", 12, { 303, 174 });
    objectsHandler->loadTextIntoHolder("Damage:", 12, { 303, 187 });
    objectsHandler->loadTextIntoHolder("AoE:", 12, { 303, 200 });
    objectsHandler->loadTextIntoHolder("Exp:", 12, { 303, 213 });
    objectsHandler->loadTextIntoHolder("Armor:", 12, { 303, 226 });
    objectsHandler->loadTextIntoHolder("100", 12, { 373, 161 });
    objectsHandler->loadTextIntoHolder("2", 12, { 373, 174 });
    objectsHandler->loadTextIntoHolder("100", 12, { 373, 187 });
    objectsHandler->loadTextIntoHolder("100", 12, { 373, 200 });
    objectsHandler->loadTextIntoHolder("100", 12, { 373, 213 });
    objectsHandler->loadTextIntoHolder("0", 12, { 373, 226 });
    objectsHandler->addVectorToSpriteHolder();
    playChoiceTexture = objectsHandler->loadTexture({ 244, 154 }, "MapThumbnails");
    if (!playChoiceTexture) 
        return true;
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 122, 77 }, spriteHolderIndex + 1);
    objectsHandler->getSpritePointer(spriteHolderIndex + 1, -1)->setPosition({ 155, 5 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 0, 0 }, spriteHolderIndex+1);
    objectsHandler->getSpritePointer(spriteHolderIndex + 1, -1)->setPosition({ 155, 5 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 122, 0 }, spriteHolderIndex+1);
    objectsHandler->getSpritePointer(spriteHolderIndex + 1, -1)->setPosition({ 155, 5 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 0, 77 }, spriteHolderIndex + 1);
    objectsHandler->getSpritePointer(spriteHolderIndex + 1, -1)->setPosition({ 155, 5 });
    objectsHandler->addVectorToSpriteHolder();
    playChoiceTexture = objectsHandler->loadTexture({ 244, 221 }, "CharacterThumbnails");
    if (!playChoiceTexture) 
        return true;
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 0, 154 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 155, 94 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 0, 0 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 155, 94 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 122, 0 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 155, 94 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 0, 77 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 155, 94 });
    objectsHandler->loadSpriteIntoHolder(*playChoiceTexture, { 122,77 }, { 122, 77 }, spriteHolderIndex + 2);
    objectsHandler->getSpritePointer(spriteHolderIndex + 2, -1)->setPosition({ 155, 94 });
    Unlocks unlocks;
    unlockedChars = unlocks.loadUnlocked("CharactersUnlocked");
    unlockedMaps = unlocks.loadUnlocked("MapsUnlocked");
    refreshSelection();
    refreshCharacterStats();
    return false;
}

void PlayChoice::refreshCharacterStats() {
    CharacterDetails stats = getCharacterStats(*selectedPlayer);
    objectsHandler->getTextPointer(8)->setString(std::to_string((int) stats.baseHp));
    char buffer[4];
    std::snprintf(buffer, 4, "%.1f", stats.baseMs);
    std::string str(buffer);
    objectsHandler->getTextPointer(9)->setString(str);
    objectsHandler->getTextPointer(10)->setString(std::to_string((int)(stats.baseDamage*100)).append("%"));
    objectsHandler->getTextPointer(11)->setString(std::to_string((int)(stats.baseAoe * 100)).append("%"));
    objectsHandler->getTextPointer(12)->setString(std::to_string((int)(stats.baseExp * 100)).append("%"));
    objectsHandler->getTextPointer(13)->setString(std::to_string((int)stats.baseArmor));
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
    for (sf::Text& text : *objectsHandler->getTextHolder())
        text.setFillColor(sf::Color::White);
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex, i)->setColor(sf::Color::White);
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex+1); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex+1, i)->setColor({255, 255, 255, 0});
    if (selectedRow == 2 || selectedRow == 3)
        objectsHandler->getTextPointer(selectedRow - 2)->setFillColor(GREEN);
    else
        objectsHandler->getSpritePointer(spriteHolderIndex, selectedRow + 1)->setColor(GREEN);
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
    if (*selectedMap == 0) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 5)->setColor(RED);
    else if (*selectedMap == NUMBEROFMAPS - 1) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 6)->setColor(RED);
    if(*selectedPlayer == 0) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 7)->setColor(RED);
    else if (*selectedPlayer == NUMBEROFCHARS - 1) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 8)->setColor(RED);
}