#include "ObjectsHandler.h"

bool ObjectsHandler::loadFont() {
    if (!font.openFromFile("Resources/font.otf"))
    {
        return true;
    }
    return false;
}

int ObjectsHandler::getSpriteHolderSize(int collectionIndex) {
    return spriteHolder[collectionIndex]->size();
}

sf::Texture* ObjectsHandler::loadTexture(sf::Vector2i size, std::string fileName) {
    std::string fullFileName = "Resources/" + fileName + ".png";
    if (textureHolder.find(fullFileName) != textureHolder.end()) 
        return &textureHolder[fullFileName];
    sf::Texture texture;
    if (!texture.loadFromFile(fullFileName, false, sf::IntRect({0, 0}, size)))
        return nullptr;
    textureHolder[fullFileName] = std::move(texture);
    return &textureHolder[fullFileName];
}

void ObjectsHandler::loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, int index) {
    sf::Sprite sprite = sf::Sprite(texture, sf::IntRect(position, size));
    spriteHolder.at(index)->push_back(sprite);
}

int ObjectsHandler::addVectorToSpriteHolder() {
    std::vector<sf::Sprite>* newVector = new std::vector<sf::Sprite>;
    spriteHolder.push_back(newVector);
    return spriteHolder.size() - 1;
}

void ObjectsHandler::clearSpriteHolder() {
    for (std::vector<sf::Sprite>* var : spriteHolder) {
        var->clear();
        delete var;
    }
    spriteHolder.clear();
}

std::vector <std::vector<sf::Sprite>*>* ObjectsHandler::getSpriteHolder() {
    return &spriteHolder;
}

sf::Sprite* ObjectsHandler::getSpritePointer(int collectionIndex, int spriteIndex) {
    int realIndex = (spriteIndex == -1) ? spriteHolder.at(collectionIndex)->size() - 1 : spriteIndex;
    return &(spriteHolder.at(collectionIndex))->at(realIndex);
}

std::vector <sf::Text>* ObjectsHandler::getTextHolder() {
    return &textHolder;
}

sf::Text* ObjectsHandler::getTextPointer(int textIndex) {
    int realIndex = (textIndex == -1) ? textHolder.size() - 1 : textIndex;
    return &textHolder.at(realIndex);
}

void ObjectsHandler::clearTextHolder() {
    textHolder.clear();
}

void ObjectsHandler::loadTextIntoHolder(std::string readText, unsigned char size, sf::Vector2f position) {
    sf::Text text = sf::Text(font, readText, size);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);
    textHolder.push_back(text);
}

float ObjectsHandler::calculateTextWidth(std::string readText, unsigned char size) {
    return sf::Text(font, readText, size).getGlobalBounds().size.x;
}

void ObjectsHandler::generateChunk(int chunkX, int chunkY) {
    std::pair pair{ chunkX, chunkY };
    if (chunkMap.find(pair) != chunkMap.end()) return;
    Chunk* chunk = new Chunk;
    chunk->generate = true;
    chunkMap[pair] = chunk;
    Chunk& storedChunk = *chunkMap[pair];
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    sf::Texture* texture = loadTexture({ 32, 16 }, "TexturesMap1");
    for (int i = 0; i < CHUNKSIZE; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) {
            float value = noise.GetNoise((float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE);
            int terrain = (value < 0.55f) ? 1 : 0;
            storedChunk.tiles[i][j].type = terrain;
            storedChunk.tiles[i][j].sprite = new sf::Sprite(*texture, sf::IntRect({16 * storedChunk.tiles[i][j].type, 0}, {16, 16}));
        }
    }
}

std::unordered_map<std::pair<int, int>, Chunk*, PairHash> ObjectsHandler::getChunkMap() {
    return chunkMap;
}