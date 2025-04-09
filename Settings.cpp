#include "Settings.h"

void SettingsScene::refreshSelection() {
    for (sf::Text& text : *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    objectsHandler->getTextPointer(8)->setFillColor(DARKRED);
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
    else if (selectedRow == 2) 
        objectsHandler->getTextPointer(8)->setFillColor(GREEN);
    else 
        objectsHandler->getTextPointer(9)->setFillColor(GREEN);
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
            if (selectedRow == 4)
                selectedRow = 0;
            selectedColumn = 0;
            refreshSelection();
            break;
        case sf::Keyboard::Key::Up:
            selectedRow--;
            if (selectedRow == -1)
                selectedRow = 3;
            selectedColumn = 0;
            refreshSelection();
            break;
        case sf::Keyboard::Key::Left:
            selectedColumn--;
            if (selectedColumn == -1)
                selectedColumn = columnNumbers[selectedRow] - 1;
            refreshSelection();
            break;
        case sf::Keyboard::Key::Right:
            selectedColumn++;
            if (selectedColumn == columnNumbers[selectedRow])
                selectedColumn = 0;
            refreshSelection();
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
                refreshSelection();
                break;
            case 1:
                if (selectedColumn == 0) 
                    display->setFullscreen(full);
                else if (selectedColumn == 1) 
                    display->setFullscreen(borders);
                else 
                    display->setFullscreen(windowed);
                refreshSelection();
                break;
            case 2:
                *sceneLabel = RESETCHOICE;
                return true;
            case 3:
                *sceneLabel = MAINMENU;
                return true;
            }
            break;
        };
    }
    return false;
}

bool SettingsScene::init() {
    selectedRow = selectedColumn = 0;
    sf::Texture* settingsMenuTexture = objectsHandler->loadTexture({ 432, 270 }, "SettingsBG");
    if (!settingsMenuTexture) 
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*settingsMenuTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
    sf::Texture* buttonsTexture = objectsHandler->loadTexture({ 434, 76 }, "ButtonSprites");
    if (!buttonsTexture) 
        return true;
    for (int i = 0; i < 3; i++) {
        objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 27 + 144.0f * i, 38 });
    }
    for (int i = 0; i < 3; i++) {
        objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 27 + 144.0f * i, 118 });
    }
    objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 170 });
    objectsHandler->loadSpriteIntoHolder(*buttonsTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 223 });
    objectsHandler->loadTextIntoHolder("Resolution", 32, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Resolution", 32)) / 2, -4 });
    objectsHandler->loadTextIntoHolder("Mode", 32, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Mode", 32)) / 2, 80 });
    objectsHandler->loadTextIntoHolder("1280x800", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1280x800", 21)) / 2 - 144.0f, 43 });
    objectsHandler->loadTextIntoHolder("1440x900", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1440x900", 21)) / 2, 43 });
    objectsHandler->loadTextIntoHolder("1680x1050", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1680x1050", 21)) / 2 + 144.0f, 43 });
    objectsHandler->loadTextIntoHolder("Fullscreen", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Fullscreen", 21)) / 2 - 144.0f, 122 });
    objectsHandler->loadTextIntoHolder("With bars", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("With bars", 21)) / 2 - 1.0f, 122 });
    objectsHandler->loadTextIntoHolder("Windowed", 21, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Windowed", 21)) / 2 + 144.0f, 122 });
    objectsHandler->loadTextIntoHolder("Reset", 27, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Reset", 27)) / 2, 171 });
    objectsHandler->getTextPointer(-1)->setFillColor(DARKRED);
    objectsHandler->loadTextIntoHolder("Exit", 27, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Exit", 27)) / 2, 224 });
    refreshSelection();
    return false;
}

void SettingsScene::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
    display->saveToFile();
}