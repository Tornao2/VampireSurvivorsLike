    #include "PlaySpace.h"

bool PlaySpace::logic(std::optional<sf::Event> gameEvent) {   
    if (gameEvent->is<sf::Event::Closed>()) {
        return true;
    }
    return false;
}

void PlaySpace::realTimeLogic() {
    float msMod = player.getMoveMod();
    float move = msMod * 2 + 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        moveWithCollision({0, move});
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveWithCollision({ 0, -move });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        moveWithCollision({ move, 0 });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        moveWithCollision({ -move, 0 });
    }
    int playerChunkX = player.getX() / (CHUNKSIZE * TILESIZE);
    int playerChunkY = player.getY() / (CHUNKSIZE * TILESIZE);
    for (int dx = -2; dx < 3; dx++) {
        for (int dy = -2; dy < 3; dy++) {
            objectsHandler->generateChunk(playerChunkX + dx, playerChunkY + dy);
        }
    }
    int seconds = static_cast<int>(timer.getElapsedTime().asSeconds());
    int minutes = seconds / 60;
    seconds = seconds - minutes * 60;
    std::ostringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    objectsHandler->getTextPointer(0)->setString(timeStream.str());
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setTextureRect({ {0, 8} , { (int)(((float) player.getXp() / player.getXpToNext()) * 414), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setTextureRect({ {0, 16} , { (int)(((float)player.getCurrentHp() / player.getEffectiveHp()) * 200), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 0)->setPosition({ 16+player.getX()-208, 1 + player.getY() - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setPosition({ 16 + player.getX() - 208, 1 + player.getY() - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 2)->setPosition({ 16 + player.getX() - 208, 10 + player.getY() - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setPosition({ 16 + player.getX() - 208, 10 + player.getY() - 123 });

}

void PlaySpace::setMapAndChar(int readMap, int readChar) {
    mapNumber = readMap;
    charNumber = readChar;
}

bool PlaySpace::init() {
    sf::Texture* spaceTexture = objectsHandler->loadTexture({ 32, 24 }, "CharacterSprites");
    if (!spaceTexture) {
        return true;
    }
    playerHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*spaceTexture, { 16,24 }, { 16 * charNumber, 0 }, playerHolderIndex);
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->setPosition({ 208, 123 });
    player.setSizes(208, 123, 16, 24);
    player.setMods();
    player.setHp(player.getEffectiveHp());
    objectsHandler->loadTextIntoHolder("00:00", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("00:00", 24)) / 2, 11 });
    objectsHandler->loadTextIntoHolder("LVL: 1", 8, { SCENEWIDTH/52 - objectsHandler->calculateTextWidth("LVL: 1", 8)/2 , 0 });
    sf::Texture* hudTexture = objectsHandler->loadTexture({ 414, 24 }, "HudElements");
    hudHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 414,8 }, { 0, 0 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 16, 1 });
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 414,8 }, { 0, 8 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 16, 1 });
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 200,8 }, { 0, 0 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 16, 10 });
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 200,8 }, { 0, 16 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 16, 10 });
    return false;
}

void PlaySpace::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
    timer.stop();
}

CharacterData PlaySpace::getPlayerData() {
    return player;
}

void PlaySpace::moveWithCollision(std::pair<float, float> move) {
    player.move(move.first, move.second);
    int playerChunkX = player.getX() / (CHUNKSIZE * TILESIZE);
    int playerChunkY = player.getY() / (CHUNKSIZE * TILESIZE);
    std::pair<int, int> tempPair = { playerChunkX , playerChunkY };
    sf::FloatRect playerBounds(
        {player.getX(),
        player.getY() + 8
        },
        { (float)player.getWidth(),
        (float)player.getWidth() }
    );
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            std::pair<int, int> realPair = { playerChunkX +a, playerChunkY+b };
            auto tempMap = objectsHandler->getChunkMap().at(realPair);
            for (int i = 0; i < CHUNKSIZE; i++) {
                for (int j = 0; j < CHUNKSIZE; j++) {
                    if (tempMap->tiles[i][j].type == 0) {
                        sf::FloatRect tileBounds({
                            (float)(playerChunkX+a)*TILESIZE * CHUNKSIZE + i * TILESIZE,
                            (float)(playerChunkY+b)*TILESIZE * CHUNKSIZE + j * TILESIZE
                            },
                            { (float)TILESIZE,
                            (float)TILESIZE }
                        );
                        if (tileBounds.findIntersection(playerBounds).has_value()) {
                            player.move(-move.first, -move.second);
                            return;
                        }
                    }
                }
            }
        }
    }
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->move({ move.first, move.second });
}