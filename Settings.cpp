#include "Settings.h"

void SettingsScene::refreshSelection() {
    for (sf::Text& text : *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    objectsHandler->getTextPointer(9)->setFillColor(RED);
    switch ((unsigned int) display->getWindowSize().x) {
        case 1280:
            objectsHandler->getTextPointer(2)->setFillColor(BLUE);
            break;
        case 1440:
            objectsHandler->getTextPointer(3)->setFillColor(BLUE);
            break;
        case 1680:
            objectsHandler->getTextPointer(4)->setFillColor(BLUE);
            break;
    }
    if (display->getFullscreen() == full) 
        objectsHandler->getTextPointer(5)->setFillColor(BLUE);
    else if (display->getFullscreen() == borders)
        objectsHandler->getTextPointer(6)->setFillColor(BLUE);
    else 
        objectsHandler->getTextPointer(7)->setFillColor(BLUE);
    if (selectedRow == 0) 
        objectsHandler->getTextPointer(selectedColumn + 2)->setFillColor(GREEN);
    else if (selectedRow == 1) 
        objectsHandler->getTextPointer(selectedColumn + 5)->setFillColor(GREEN);
    else  
        objectsHandler->getTextPointer(6 + selectedRow)->setFillColor(GREEN);
}

void SettingsScene::setDisplay(Display* readDisplay) {
    display = readDisplay;
}

bool SettingsScene::eventLogic(std::optional<sf::Event> gameEvent) {
    static unsigned char columnNumbers[] = { 3, 3, 1, 1 };
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        switch (gameEvent->getIf<sf::Event::KeyPressed>()->code) {
        case sf::Keyboard::Key::Down:
            selectedRow++;
            if (selectedRow == 5)
                selectedRow = 0;
            break;
        case sf::Keyboard::Key::Up:
            selectedRow--;
            if (selectedRow == -1)
                selectedRow = 4;
            break;
        case sf::Keyboard::Key::Left:
            if (selectedRow == 0 || selectedRow == 1) {
                selectedColumn--;
                if (selectedColumn == -1)
                    selectedColumn = columnNumbers[selectedRow] - 1;
            }
            else if (selectedRow == 2 && *soundVolume != 0) {
                (*soundVolume)--;
                objectsHandler->getTextPointer(11)->setString(std::to_string(*soundVolume));
                objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 132.0f + (int) 169.0f * (*soundVolume) / 100, 154 });
            }
            break;
        case sf::Keyboard::Key::Right:
            if (selectedRow == 0 || selectedRow == 1) {
                selectedColumn++;
                if (selectedColumn == columnNumbers[selectedRow])
                    selectedColumn = 0;
            }
            else if (selectedRow == 2 && *soundVolume != 100) {
                (*soundVolume)++;
                objectsHandler->getTextPointer(11)->setString(std::to_string(*soundVolume));
                objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 132.0f + (int) 169.0f * (*soundVolume) / 100, 154 });
            }
            break;
        case sf::Keyboard::Key::Enter:
            switch (selectedRow) {
                case 0:
                    if (selectedColumn == 0) 
                        display->setResolution({ 1280, 800 });
                    else if (selectedColumn == 1) 
                        display->setResolution({1440, 900});
                    else 
                        display->setResolution({ 1680, 1050 });
                    break;
                case 1:
                    if (selectedColumn == 0) 
                        display->setFullscreen(full);
                    else if (selectedColumn == 1) 
                        display->setFullscreen(borders);
                    else 
                        display->setFullscreen(windowed);
                    break;
                case 3:
                    *sceneLabel = RESETCHOICE;
                    return true;
                case 4:
                    *sceneLabel = MAINMENU;
                    return true;
                }
            break;
        };
        refreshSelection();
    }
    return false;
}

bool SettingsScene::init() {
    sf::Texture* backgroundTexture = objectsHandler->loadTexture({ 432, 270 }, "SettingsBG");
    if (!backgroundTexture)
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*backgroundTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
    sf::Texture* buttonsTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonsTexture) 
        return true;
    for (int i = 0; i < 3; i++) {
        objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 27 + 144.0f * i, 26 });
    }
    for (int i = 0; i < 3; i++) {
        objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 27 + 144.0f * i, 98 });
    }
    objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 188 });
    objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 230 }); 
    objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 236,38 }, { 0, 64 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 120, 144 });
    objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 1,18 }, { 236, 64 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 132.0f + (int)169.0f * (*soundVolume) / 100, 154 });
    objectsHandler->loadTextIntoHolder("Resolution", 32, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Resolution", 32)) / 2, -9 });
    objectsHandler->loadTextIntoHolder("Mode", 32, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Mode", 32)) / 2, 62 });
    objectsHandler->loadTextIntoHolder("1280x800", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1280x800", 21)) / 2 - 144.0f, 30 });
    objectsHandler->loadTextIntoHolder("1440x900", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1440x900", 21)) / 2, 30 });
    objectsHandler->loadTextIntoHolder("1680x1050", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1680x1050", 21)) / 2 + 144.0f, 30 });
    objectsHandler->loadTextIntoHolder("Fullscreen", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Fullscreen", 21)) / 2 - 144.0f, 103 });
    objectsHandler->loadTextIntoHolder("With bars", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("With bars", 21)) / 2 - 1.0f, 103 });
    objectsHandler->loadTextIntoHolder("Windowed", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Windowed", 21)) / 2 + 144.0f, 103 });
    objectsHandler->loadTextIntoHolder("Volume", 27, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Volume", 27)) / 2 - 144.0f, 142 });
    objectsHandler->loadTextIntoHolder("Reset", 27, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Reset", 27)) / 2, 189 });
    objectsHandler->getTextPointer(-1)->setFillColor(RED);
    objectsHandler->loadTextIntoHolder("Exit", 27, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Exit", 27)) / 2, 231 });
    objectsHandler->loadTextIntoHolder(std::to_string(*soundVolume), 27, {315, 145});
    refreshSelection();
    return false;
}


void SettingsScene::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
    display->saveToFile();
    saveVolume();
}

void SettingsScene::saveVolume() {
    std::ofstream outFile("Resources/Misc.txt");
    outFile << (*soundVolume);
    outFile.close();
}