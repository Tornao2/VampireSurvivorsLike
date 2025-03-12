#include "MainMenu.h"

bool MainMenu::logic() {
    return true;
}

bool MainMenu::init() {
    sf::Texture* mainMenuTexture = spriteHandler->loadTexture({ 400, 600 }, "MainMenu");
    if (!mainMenuTexture) return true;
    spriteHolderIndex = spriteHandler->addVectorToSpriteHolder();
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 400,100 }, { 0, 100 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({200, 50.0f + 125.0f * i});
    }
    for (int i = 0; i < 4; i++) {
        spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 400,100 }, { 0, 200 + i * 100 }, spriteHolderIndex);
        spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 200, 50.0f + 125.0f * i });
    }
    spriteHandler->loadSpriteIntoHolder(*mainMenuTexture, { 400,100 }, { 0, 0 }, spriteHolderIndex);
    spriteHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 200, 50. });
    return false;
}