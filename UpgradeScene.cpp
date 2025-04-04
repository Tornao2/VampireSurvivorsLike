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
    sf::Texture* upgradesTexture = objectsHandler->loadTexture({ 380, 242 }, "Upgrades");
    if (!upgradesTexture) 
        return true;
    spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadTextIntoHolder(modifiers.getCoins(), 30, { (SCENEWIDTH - objectsHandler->calculateTextWidth(modifiers.getCoins(), 30)) / 2, -4 });
    objectsHandler->loadSpriteIntoHolder(*upgradesTexture, { 380,190 }, { 0, 0 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 26, 30 });
    objectsHandler->loadSpriteIntoHolder(*upgradesTexture, { 122,42 }, { 67, 190 }, spriteHolderIndex);
    objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 155, 224 });
    objectsHandler->loadTextIntoHolder("Exit", 36, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Exit", 36)) / 2, 221 });
    int modNumber = 0;
    for (ModifierNode node : *modifiers.getVector()) {
        objectsHandler->loadSpriteIntoHolder(*upgradesTexture, { 67,52 }, { 0, 190 }, spriteHolderIndex);
        objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 34 + 74.0f * (modNumber % 5), 37 + 60.0f * (modNumber / 5) });
        objectsHandler->loadTextIntoHolder(node.name, 14, {68 + 74.0f * (modNumber % 5) - objectsHandler->calculateTextWidth(node.name, 14)/2, 38 + 60.0f * (modNumber / 5)});
        objectsHandler->loadTextIntoHolder(modifiers.getModStrength(modNumber), 10, {68 + 74.0f * (modNumber % 5) - objectsHandler->calculateTextWidth(modifiers.getModStrength(modNumber), 10) / 2, 74 + 60.0f * (modNumber / 5)});
        objectsHandler->loadTextIntoHolder(modifiers.getModLevel(modNumber), 22, {68 + 74.0f * (modNumber % 5) - objectsHandler->calculateTextWidth(modifiers.getModLevel(modNumber), 22) / 2, 52 + 60.0f * (modNumber / 5)});
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
            objectsHandler->getSpritePointer(spriteHolderIndex, 2 + i)->setColor(BLUE);
    }
    if (selectedRow < upgrRowsAmount) 
        objectsHandler->getSpritePointer(spriteHolderIndex, 2 + 5 * selectedRow + selectedColumn)->setColor(GREEN);
    else {
        objectsHandler->getSpritePointer(spriteHolderIndex, 1)->setColor(GREEN);
        objectsHandler->getTextPointer(1)->setFillColor(GREEN);
    }
}
