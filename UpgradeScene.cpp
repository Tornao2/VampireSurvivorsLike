#include "UpgradeScene.h"

void UpgradeScene::loadModifiers() {
    modifiers.loadModifiersFromFile();
    colAmounts = modifiers.getColumnAmounts();
    upgrRowsAmount = modifiers.getRowAmount();
}

bool UpgradeScene::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        switch (gameEvent->getIf<sf::Event::KeyPressed>()->code) {
        case sf::Keyboard::Key::Down:
            selectedRow++;
            if (selectedRow == upgrRowsAmount + 1) 
                selectedRow = 0;
            if (selectedRow < upgrRowsAmount) {
                if (selectedColumn > colAmounts[selectedRow] - 1) 
                    selectedColumn = colAmounts[selectedRow] - 1;
            }
            refreshSelection();
            break;
        case sf::Keyboard::Key::Up:
            selectedRow--;
            if (selectedRow == -1) 
                selectedRow = upgrRowsAmount;
            if (selectedRow < upgrRowsAmount) {
                if (selectedColumn > colAmounts[selectedRow] - 1) 
                    selectedColumn = colAmounts[selectedRow] - 1;
            }
            refreshSelection();
            break;
        case sf::Keyboard::Key::Left:
            if (selectedRow < upgrRowsAmount) {
                selectedColumn--;
                if (selectedColumn == -1)
                    selectedColumn = colAmounts[selectedRow] - 1;
                refreshSelection();
            }
            break;
        case sf::Keyboard::Key::Right:
            if (selectedRow < upgrRowsAmount) {
                selectedColumn++;
                if (selectedColumn == colAmounts[selectedRow])
                    selectedColumn = 0;
                refreshSelection();
            }
            break;
        case sf::Keyboard::Key::Enter:
            if (selectedRow < upgrRowsAmount) {
                modifiers.increaseLevel(selectedRow * 5 + selectedColumn);
                objectsHandler->getTextPointer(0)->setString(modifiers.getCoins());
                objectsHandler->getTextPointer(4 + 3 * (selectedRow * 5 + selectedColumn))->setString(modifiers.getModLevel(selectedRow * 5 + selectedColumn));
            }
            else {
                *sceneLabel = MAINMENU;
                return true;
            }
            break;
        };
    }
    return false;
}

bool UpgradeScene::init() {
    sf::Texture* upgradesTexture = objectsHandler->loadTexture({ 432, 270 }, "UpgradesBG");
    if (!upgradesTexture) 
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*upgradesTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 76 }, "ButtonSprites");
    if (!buttonTexture)
        return true;
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 171, 224 });
    objectsHandler->loadTextIntoHolder(modifiers.getCoins(), 30, { (SCENEWIDTH - objectsHandler->calculateTextWidth(modifiers.getCoins(), 30)) / 2, -4 });
    objectsHandler->loadTextIntoHolder("Exit", 27, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Exit", 27)) / 2, 224 });
    int modNumber = 0;
    for (ModifierNode node : *modifiers.getVector()) {
        objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 74,56 }, { 360, 0 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 34 + 76.0f * (modNumber % 5), 37 + 60.0f * (modNumber / 5) });
        objectsHandler->loadTextIntoHolder(node.name, 16, {72 + 76.0f * (modNumber % 5) - objectsHandler->calculateTextWidth(node.name, 16)/2, 37 + 60.0f * (modNumber / 5)});
        objectsHandler->loadTextIntoHolder(modifiers.getModStrength(modNumber), 13, { 71 + 76.0f * (modNumber % 5) - objectsHandler->calculateTextWidth(modifiers.getModStrength(modNumber), 13) / 2, 74 + 60.0f * (modNumber / 5)});
        objectsHandler->loadTextIntoHolder(modifiers.getModLevel(modNumber), 24, { 71 + 76.0f * (modNumber % 5) - objectsHandler->calculateTextWidth(modifiers.getModLevel(modNumber), 24) / 2, 51 + 60.0f * (modNumber / 5)});
        modNumber++;
    }
    refreshSelection();
    return false;
}

void UpgradeScene::cleanUp() {
    modifiers.saveModifiersToFile();
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
}

void UpgradeScene::refreshSelection() {
    for (sf::Text& text : *objectsHandler->getTextHolder()) 
        text.setFillColor(sf::Color::White);
    for (int i = 0; i < objectsHandler->getSpriteHolderSize(spriteHolderIndex); i++) 
        objectsHandler->getSpritePointer(spriteHolderIndex, i)->setColor(sf::Color::White);
    for (int i = 0; i < modifiers.getVector()->size(); i++) {
        if (modifiers.getVector()->at(i).currentLevel == modifiers.getVector()->at(i).maxLevel) 
            objectsHandler->getSpritePointer(spriteHolderIndex, 2 + i)->setColor(DARKRED);
    }
    if (selectedRow < upgrRowsAmount) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 2 + 5 * selectedRow + selectedColumn)->setColor(GREEN);
    else {
        objectsHandler->getTextPointer(1)->setFillColor(GREEN);
    }
}
