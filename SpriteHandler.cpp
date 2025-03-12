#include "SpriteHandler.h"

sf::Texture* SpriteHandler::loadTexture(sf::Vector2i size, std::string fileName) {
    std::string fullFileName = "Resources/" + fileName + ".png";
    if (textureHolder.find(fullFileName) != textureHolder.end()) 
        return &textureHolder[fullFileName];
    sf::Texture texture;
    if (!texture.loadFromFile(fullFileName, false, sf::IntRect({0, 0}, size)))
        return nullptr;
    textureHolder[fullFileName] = std::move(texture);
    return &textureHolder[fullFileName];
}

void SpriteHandler::loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, int index) {
    sf::Sprite sprite = sf::Sprite(texture, sf::IntRect(position, size));
    std::visit([&sprite](auto container) {
        container->push_back(sprite);
    }, spriteHolder->at(index));
}

void SpriteHandler::destroyTextures() {
    textureHolder.clear();
}

int SpriteHandler::addVectorToSpriteHolder() {
    std::vector<sf::Sprite>* newVector = new std::vector<sf::Sprite>;
    spriteHolder->push_back(newVector);
    return spriteHolder->size() - 1;
}

int SpriteHandler::addListToSpriteHolder() {
    std::list<sf::Sprite>* newList = new std::list<sf::Sprite>;
    spriteHolder->push_back(newList);
    return spriteHolder->size() - 1;
}

void SpriteHandler::clearSpriteHolder() {
    for (ListOrVector var : *spriteHolder) {
        std::visit([](auto* container) {
            container->clear();
            delete container;
        }, var);
    }
    spriteHolder->clear();
}

std::vector <ListOrVector>** SpriteHandler::getSpriteHolder() {
    return &spriteHolder;
}

sf::Sprite* SpriteHandler::getSpritePointer(int collectionIndex, int spriteIndex) {
    return std::visit([spriteIndex](auto container) -> sf::Sprite* {
        int realIndex = (spriteIndex == -1) ? container->size() - 1 : spriteIndex;
        auto it = container->begin();
        std::advance(it, realIndex);
        return &(*it);
    }, spriteHolder->at(collectionIndex));
}