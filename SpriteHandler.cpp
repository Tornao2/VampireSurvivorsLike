#include "SpriteHandler.h"

sf::Texture* SpriteHandler::loadTexture(sf::Vector2i size, std::string fileName) {
    std::string fullFileName = "Resources/" + fileName + ".png";
    if (textureHolder.find(fullFileName) != textureHolder.end()) {
        return &textureHolder[fullFileName];
    }
    sf::Texture texture;
    if (!texture.loadFromFile(fullFileName, false, sf::IntRect({0, 0}, size)))
    {
        return nullptr;
    }
    textureHolder[fullFileName] = std::move(texture);
    return &textureHolder[fullFileName];
}

sf::Sprite SpriteHandler::loadSprite(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position) {
    return sf::Sprite(texture, sf::IntRect(position, size));
}