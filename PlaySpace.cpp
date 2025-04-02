    #include "PlaySpace.h"

bool PlaySpace::logic(std::optional<sf::Event> gameEvent) {   
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    return false;
}

void PlaySpace::realTimeLogic() {
    checkChunks();
    moveWithCollision();
    setTimer();
    drawHud();
}

void PlaySpace::drawHud() {
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setTextureRect({ {0, 8} , { (int)(((float)playerData.getXp() / playerData.getXpToNext()) * 414), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setTextureRect({ {0, 16} , { (int)(((float)playerData.getCurrentHp() / playerData.getEffectiveHp()) * 200), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 0)->setPosition({ 16 + playerData.getX() - 208, 1 + playerData.getY() - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setPosition({ 16 + playerData.getX() - 208, 1 + playerData.getY() - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 2)->setPosition({ 16 + playerData.getX() - 208, 10 + playerData.getY() - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setPosition({ 16 + playerData.getX() - 208, 10 + playerData.getY() - 123 });
}

void PlaySpace::setTimer() {
    int seconds = static_cast<int>(timer.getElapsedTime().asSeconds());
    int minutes = seconds / 60;
    seconds = seconds - minutes * 60;
    std::ostringstream timeStream;
    timeStream.clear();
    timeStream << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    objectsHandler->getTextPointer(0)->setString(timeStream.str());
}

void PlaySpace::checkChunks() {
    int playerChunkX = (int)playerData.getX() / (CHUNKSIZE * TILESIZE);
    int playerChunkY = (int)playerData.getY() / (CHUNKSIZE * TILESIZE);
    for (int dx = -2; dx < 3; dx++)
        for (int dy = -2; dy < 3; dy++)
            objectsHandler->generateChunk(playerChunkX + dx, playerChunkY + dy);
}

void PlaySpace::setMapAndChar(int readMap, int readChar) {
    mapNumber = readMap;
    charNumber = readChar;
}

bool PlaySpace::init() {
    sf::Texture* spaceTexture = objectsHandler->loadTexture({ 32, 24 }, "CharacterSprites");
    if (!spaceTexture) 
        return true;
    playerHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*spaceTexture, { 16,24 }, { 16 * charNumber, 0 }, playerHolderIndex);
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->setPosition({ 208, 123 });
    playerData.setSizes(208, 123, 16, 24);
    playerData.setMods();
    playerData.setHp(playerData.getEffectiveHp());
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
    return playerData;
}

void PlaySpace::moveWithCollision() {
    float baseMs = 2;
    float move = playerData.getMoveMod() * baseMs + baseMs;
    std::pair <float, float> moveStep = { 0, 0 };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        moveStep.second = move;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        moveStep.second = -move;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        moveStep.first =  move;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        moveStep.first = -move;
    playerData.move(moveStep.first, moveStep.second);
    int playerChunkX = playerData.getX() / (CHUNKSIZE * TILESIZE);
    int playerChunkY = playerData.getY() / (CHUNKSIZE * TILESIZE);
    sf::FloatRect playerBounds(
        { playerData.getX(),playerData.getY() + 8},
        { (float)playerData.getWidth(), (float)playerData.getWidth() }
    );
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            auto tempMap = objectsHandler->getChunkMap().at({ playerChunkX + a, playerChunkY + b });
            for (int i = 0; i < CHUNKSIZE; i++) {
                for (int j = 0; j < CHUNKSIZE; j++) {
                    if (tempMap->tiles[i][j].type == 0) {
                        sf::FloatRect tileBounds({
                            (float)(playerChunkX+a)*TILESIZE * CHUNKSIZE + i * TILESIZE, (float)(playerChunkY+b)*TILESIZE * CHUNKSIZE + j * TILESIZE},
                            { (float)TILESIZE, (float)TILESIZE }
                        );
                        if (tileBounds.findIntersection(playerBounds).has_value()) {
                            playerData.move(-moveStep.first, -moveStep.second);
                            return;
                        }
                    }
                }
            }
        }
    }
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->move({ moveStep.first, moveStep.second });
}