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

void SpriteHandler::loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*> collection) {
    sf::Sprite sprite = sf::Sprite(texture, sf::IntRect(position, size));
    std::visit([&sprite](auto container) {
        container->push_back(sprite);
    }, collection);
}

void SpriteHandler::destroyTextures() {
    textureHolder.clear();
}

std::vector<sf::Sprite>* SpriteHandler::addVectorToSpriteHolder() {
    std::vector<sf::Sprite>* newVector = new std::vector<sf::Sprite>;
    spriteHolder.push_back(newVector);
    return newVector;
}

std::list<sf::Sprite>* SpriteHandler::addListToSpriteHolder() {
    std::list<sf::Sprite>* newList = new std::list<sf::Sprite>;
    spriteHolder.push_back(newList);
    return newList;
}

void SpriteHandler::removeCollectionFromSpriteHolder(std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*>* readCollection) {
    auto it = std::find(spriteHolder.begin(), spriteHolder.end(), *readCollection);
    if (it != spriteHolder.end()) {
        std::visit([](auto ptr) { delete ptr; }, *it);
        spriteHolder.erase(it);
    }
}

void SpriteHandler::clearSpriteHolder() {
    for (std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*> var : spriteHolder) {
        std::visit([](auto* container) {
            container->clear();
            delete container;
        }, var);
    }
    spriteHolder.clear();
}

std::vector < std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*>>& SpriteHandler::getSpriteHolder() {
    return spriteHolder;
}