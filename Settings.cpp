#include "Settings.h"

void SettingsScene::refreshSelection() {
    for (sf::Text& text : *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex, i)->setColor(sf::Color::White);
    objectsHandler->getSpritePointer(spriteHolderIndex, 6)->setColor(DARKRED);
    objectsHandler->getTextPointer(8)->setFillColor(DARKRED);
    switch ((unsigned int) display->getWindowWidth()) {
        case 1280:
            objectsHandler->getTextPointer(2)->setFillColor(BLUE);
            objectsHandler->getSpritePointer(spriteHolderIndex, 0)->setColor(BLUE);
            break;
        case 1440:
            objectsHandler->getTextPointer(3)->setFillColor(BLUE);
            objectsHandler->getSpritePointer(spriteHolderIndex, 1)->setColor(BLUE);
            break;
        case 1680:
            objectsHandler->getTextPointer(4)->setFillColor(BLUE);
            objectsHandler->getSpritePointer(spriteHolderIndex, 2)->setColor(BLUE);
            break;
    }
    if (display->getFullscreen() == full) {
        objectsHandler->getTextPointer(5)->setFillColor(BLUE);
        objectsHandler->getSpritePointer(spriteHolderIndex, 3)->setColor(BLUE);
    }
    else if (display->getFullscreen() == borders){
        objectsHandler->getTextPointer(6)->setFillColor(BLUE);
        objectsHandler->getSpritePointer(spriteHolderIndex, 4)->setColor(BLUE);
    }
    else {
        objectsHandler->getTextPointer(7)->setFillColor(BLUE);
        objectsHandler->getSpritePointer(spriteHolderIndex, 5)->setColor(BLUE);
    }
    if (selectedRow == 0) {
        objectsHandler->getTextPointer(selectedColumn + 2)->setFillColor(GREEN);
        objectsHandler->getSpritePointer(spriteHolderIndex, selectedColumn)->setColor(GREEN);
    }
    else if (selectedRow == 1) {
        objectsHandler->getTextPointer(selectedColumn + 5)->setFillColor(GREEN);
        objectsHandler->getSpritePointer(spriteHolderIndex, selectedColumn + 3)->setColor(GREEN);
    }
    else if (selectedRow == 2) {
        objectsHandler->getTextPointer(8)->setFillColor(GREEN);
        objectsHandler->getSpritePointer(spriteHolderIndex, 6)->setColor(GREEN);
    }
    else {
        objectsHandler->getTextPointer(9)->setFillColor(GREEN);
        objectsHandler->getSpritePointer(spriteHolderIndex, 7)->setColor(GREEN);
    } 
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
                    display->setResolution(1280, 800);
                else if (selectedColumn == 1) 
                    display->setResolution(1440, 900);
                else 
                    display->setResolution(1680, 1050);
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
    sf::Texture* settingsMenuTexture = objectsHandler->loadTexture({ 120, 50 }, "Settings");
    if (!settingsMenuTexture) return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadTextIntoHolder("Resolution", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Resolution", 36)) / 2, -4 });
    objectsHandler->loadTextIntoHolder("Mode", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Mode", 36)) / 2, 77 });
    objectsHandler->loadTextIntoHolder("1280x800", 30, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1280x800", 30)) / 2 - 136.0f, 40 });
    objectsHandler->loadTextIntoHolder("1440x900", 30, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1440x900", 30)) / 2, 40 });
    objectsHandler->loadTextIntoHolder("1680x1050", 30, { (SCENEWIDTH - objectsHandler->calculateTextWidth("1680x1050", 30)) / 2 + 138.0f, 40 });
    for (int i = 0; i < 3; i++) {
        objectsHandler->loadSpriteIntoHolder(*settingsMenuTexture, { 120,50 }, { 0, 0 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 20 + 138.0f * i, 35 });
    }
    objectsHandler->loadTextIntoHolder("Fullscreen", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Fullscreen", 30)) / 2 - 145.0f, 117 });
    objectsHandler->loadTextIntoHolder("With bars", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("With bars", 30)) / 2 - 5.0f, 117 });
    objectsHandler->loadTextIntoHolder("Windowed", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Windowed", 30)) / 2 + 132.0f, 117 });
    for (int i = 0; i < 3; i++) {
        objectsHandler->loadSpriteIntoHolder(*settingsMenuTexture, { 120,50 }, { 0, 0 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 20 + 138.0f * i, 115 });
    }
    objectsHandler->loadTextIntoHolder("Reset", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Reset", 36)) / 2, 167 });
    objectsHandler->getTextPointer(-1)->setFillColor(DARKRED);
    objectsHandler->loadTextIntoHolder("Exit", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Exit", 36)) / 2, 222 });
    objectsHandler->loadSpriteIntoHolder(*settingsMenuTexture, { 120,50 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 158, 167 });
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setColor(DARKRED);
    objectsHandler->loadSpriteIntoHolder(*settingsMenuTexture, { 120,50 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 158, 220 });
    refreshSelection();
    return false;
}

void SettingsScene::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
    display->saveToFile();
}