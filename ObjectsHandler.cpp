#include "ObjectsHandler.h"

bool ObjectsHandler::loadFont() {
    if (!font.openFromFile("Resources/font.otf"))
        return true;
    return false;
}

int ObjectsHandler::getSpriteHolderSize(int collectionIndex) {
    return (int) spriteHolder[collectionIndex]->size();
}

sf::Texture* ObjectsHandler::loadTexture(sf::Vector2i size, std::string fileName) {
    std::string fullFileName = "Resources/" + fileName + ".png";
    if (textureHolder.find(fullFileName) != textureHolder.end()) 
        return &textureHolder[fullFileName];
    sf::Texture texture;
    texture.setSmooth(false);
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
    return (int)spriteHolder.size() - 1;
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
    return &(spriteHolder.at(collectionIndex))->at((spriteIndex == -1) ? spriteHolder.at(collectionIndex)->size() - 1 : spriteIndex);
}

std::vector <sf::Text>* ObjectsHandler::getTextHolder() {
    return &textHolder;
}

sf::Text* ObjectsHandler::getTextPointer(int textIndex) {
    return &textHolder.at((textIndex == -1) ? textHolder.size() - 1 : textIndex);
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

void ObjectsHandler::addEnemy(int enemyId, sf::Vector2f readPos, bool readIsBoss) {
    if (readIsBoss || enemyHolder.size() < 500) {
        EnemyData* enemy = new EnemyData();
        enemy->giveStats(enemyId, readPos, readIsBoss);
        enemy->setSprite(new sf::Sprite(textureHolder.at("Resources/EnemySprites.png"), { enemy->getOffset() , {16, 24} }));
        if (readIsBoss)
            enemy->getSprite()->setScale({ 2, 2 });
        enemy->getSprite()->setPosition(readPos);
        enemyHolder.push_back(enemy);
    }
}

void ObjectsHandler::clearEnemyHolder() {
    for (EnemyData* data : enemyHolder) {
        data->clearSprite();
        delete data;
    }
    enemyHolder.clear();
}

std::list <EnemyData*>* ObjectsHandler::getEnemyHolder() {
    return &enemyHolder;
}

void ObjectsHandler::killEnemy(std::list<EnemyData*> enemiesToKill) {
    bool erased;
    for (auto it = enemyHolder.begin(); it != enemyHolder.end(); ) {
        erased = false;
        for (EnemyData* enemy : enemiesToKill) {
            if (*it == enemy) {
                enemy->clearSprite();
                it = enemyHolder.erase(it);
                erased = true;
                break;
            }
        }
        if (!erased)
            it++;
    }
}

sf::Vector2f ObjectsHandler::getClosestEnemyCords(sf::Vector2f readPlayerPos) {
    sf::Vector2f target;
    if (enemyHolder.size() != 0){
        float closestDistance = std::numeric_limits<float>::max();
        for (EnemyData* enemy : enemyHolder) {
            sf::Vector2f d = readPlayerPos - enemy->getPos();
            float distanceSq = d.x * d.x + d.y * d.y;
            if (distanceSq < closestDistance) {
                closestDistance = distanceSq;
                target = enemy->getPos();
            }
        }
    }
    else 
        target = { readPlayerPos.x + (rand() % 2) - 1, readPlayerPos.y + (rand() % 2) - 1 };
    return target;
}

void ObjectsHandler::addProjectile(float damageMod, int projectileId, sf::Vector2f readPos, sf::Vector2f readEndPos) {
    sf::Sprite* sprite = nullptr;
    switch (projectileId) {
        case 0:
            sprite = new sf::Sprite(textureHolder.at("Resources/ProjectileSprites.png"), { { 0,0 }, { 9, 9 } });
            break;
    }
    sprite->setPosition(readPos);
    Projectiles* projectile = new Projectiles(sprite, damageMod, readPos, readEndPos, projectileId);
    projectileHolder.push_back(projectile);
}

void ObjectsHandler::clearProjectileHolder() {
    for (Projectiles* projectile : projectileHolder) {
        projectile->clearSprite();
        delete projectile;
    }
    projectileHolder.clear();
}

std::list <Projectiles*>* ObjectsHandler::getProjectileHolder() {
    return &projectileHolder;
}

void ObjectsHandler::destroyProjectiles(std::list<Projectiles*> projectilesToDestroy) {
    bool erased;
    for (auto it = projectileHolder.begin(); it != projectileHolder.end(); ) {
        erased = false;
        for (Projectiles* proj : projectilesToDestroy) {
            if (*it == proj) {
                proj->clearSprite();
                it = projectileHolder.erase(it);
                erased = true;
                break;
            }
        }
        if (!erased)
            it++;
    }
}

void ObjectsHandler::addPowerUp(int powerUpId, sf::Vector2f readPos) {
    sf::Sprite* sprite = new sf::Sprite(textureHolder.at("Resources/PowerUps.png"), { { 10 * powerUpId,0 }, { 10, 10 } });
    sprite->setPosition(readPos);
    PowerUp* powerUp = new PowerUp(powerUpId, readPos, sprite);
    powerUpHolder.push_back(powerUp);
}

void ObjectsHandler::clearPowerUpHolder() {
    for (PowerUp* powerUp : powerUpHolder) {
        powerUp->deleteSprite();
        delete powerUp;
    }
    powerUpHolder.clear();
}

std::list <PowerUp*>* ObjectsHandler::getPowerUpHolder() {
    return &powerUpHolder;
}

void ObjectsHandler::destroyPowerUp(PowerUp* powerUpToDestroy) {
    auto it = std::find(powerUpHolder.begin(), powerUpHolder.end(), powerUpToDestroy);
    if (it != powerUpHolder.end()) {
        powerUpToDestroy->deleteSprite();
        powerUpHolder.erase(it);
    }
}

MapGenerator* ObjectsHandler::getMapGenerator() {
    return &generator;
}

void ObjectsHandler::setMap(int readMapId) {
    sf::Vector2i size = { 32, 32 };
    if (readMapId == 2)
        size = { 32, 16 };
    sf::Texture* texture = loadTexture(size, std::string("TexturesMap").append(std::to_string(readMapId+1)));
    generator.setMapId(readMapId);
    generator.setTextures(texture);
}