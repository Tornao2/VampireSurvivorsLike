#include "Settings.h"

void SettingsScene::refreshSelection() {

}

bool SettingsScene::logic(std::optional<sf::Event> gameEvent) {
    return false;
}

bool SettingsScene::init() {
    selectedButton = 0;
    sf::Texture* mainMenuTexture = spriteHandler->loadTexture({ 200, 300 }, "MainMenu");
    if (!mainMenuTexture) return true;
    spriteHolderIndex = spriteHandler->addVectorToSpriteHolder();
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 50 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 25.0f + 60.0f * i });
    }
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 100 + i * 50 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 25.0f + 60.0f * i });
    }
    spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 200,50 }, { 0, 0 }, spriteHolderIndex);
    spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 116, 25. });
    return false;
}

void SettingsScene::cleanUp() {
    spriteHandler->clearSpriteHolder();
}