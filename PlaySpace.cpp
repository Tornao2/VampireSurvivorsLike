    #include "PlaySpace.h"

bool PlaySpace::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    return false;
}

bool PlaySpace::realTimeLogic() {
    int seconds = static_cast<int>(timer.getElapsedTime().asSeconds());
    if (seconds >= 600) {
        *sceneLabel = MAINMENU;
        return true;
    }
    if (playerData.getCurrentHp() != 0) {
        playerData.decrementInvincibility();
        chunkLogic();
        movementLogic();
        moveEnemies();
        weaponLogic();
        moveProjectiles();
        checkProjectileCollision();
        checkEnemyHp();
        checkEnemyCollision();   
        setTimer();
        drawHud();
        respawnEnemies();
    }
    else {
        *sceneLabel = MAINMENU;
        return true;
    }
    return false;
}

void PlaySpace::weaponLogic() {
    if (objectsHandler->getEnemyHolder()->size() != 0) {
        sf::Vector2f target = objectsHandler->getClosestEnemyCords(playerData.getPos());
        static int lastFireTime = 0;
        if (static_cast<int>(timer.getElapsedTime().asSeconds()) - lastFireTime > 1) {
            lastFireTime = static_cast<int>(timer.getElapsedTime().asSeconds());
            objectsHandler->addProjectile(playerData.getDamageMod(), 0, playerData.getPos(), target);
        }
    }
}

void PlaySpace::moveProjectiles() {
    for (Projectiles* node : *objectsHandler->getProjectileHolder()) 
        node->move();
    std::list <Projectiles*> proj;
    for (Projectiles* projectile : *objectsHandler->getProjectileHolder())
        if ((projectile->getPos() - playerData.getPos()).length() >= 400)
            proj.push_back(projectile);
    objectsHandler->destroyProjectiles(proj);
}

void PlaySpace::checkProjectileCollision() {
    std::list <Projectiles*> proj;
    for (Projectiles* node : *objectsHandler->getProjectileHolder()) {
        sf::FloatRect projectileBounds(node->getPos(), node->getSize());
        for (EnemyData* enemy : *objectsHandler->getEnemyHolder()) {
            sf::FloatRect enemyBounds(enemy->getPos(), enemy->getSize());
            if (enemyBounds.findIntersection(projectileBounds).has_value()) {
                enemy->changeHealthBy(-node->getDamage());
                proj.push_back(node);
                break;
            }
        }
    }
    objectsHandler->destroyProjectiles(proj);
}

void PlaySpace::checkEnemyHp() {
    std::list <EnemyData*> enemiesToKill;
    for (EnemyData* enemy : *objectsHandler->getEnemyHolder()) {
        if (enemy->getHealth() == 0) {
            enemiesToKill.push_back(enemy);
            playerData.increaseXp(enemy->getXpForKill());
            objectsHandler->getTextPointer(1)->setString(std::string("LVL:").append(std::to_string(playerData.getLevel())));
        }
    }
    objectsHandler->killEnemy(enemiesToKill);
}

void PlaySpace::moveEnemies() {
    for (EnemyData* enemy : *objectsHandler->getEnemyHolder()) {
        sf::Vector2f dirVec = playerData.getPos() - enemy->getPos();
        float length = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
        if (fabs(length) >= 0.5) {
            dirVec /= length;
            enemy->move(dirVec);
        }
    }
}

void PlaySpace::checkEnemyCollision() {
    sf::FloatRect playerBounds(
        { playerData.getPos().x,playerData.getPos().y + playerData.getSize().y - playerData.getSize().x },
        playerData.getSize());
    for (EnemyData* enemy : *objectsHandler->getEnemyHolder()) {
        sf::FloatRect enemyBounds(enemy->getPos(), enemy->getSize());
        if (playerBounds.findIntersection(enemyBounds).has_value()) {
            playerData.changeHp(-enemy->getDamage());
            break;
        }
    }
}

sf::Vector2f PlaySpace::randomizePos() {
    sf::Vector2f returnVec;
    int side = rand() % 4;
    if (side == 0) {
        returnVec.x = rand() % SCENEWIDTH+ (int) playerData.getPos().x - SCENEWIDTH / 2;
        returnVec.y = (int) playerData.getPos().y - SCENEHEIGHT/2 - 30;
    }
    else if (side == 1) {
        returnVec.x = rand() % SCENEWIDTH + (int)playerData.getPos().x - SCENEWIDTH / 2;
        returnVec.y = (int)playerData.getPos().y + SCENEHEIGHT / 2 + 30;
    }
    else if (side == 2) {
        returnVec.x = (int)playerData.getPos().x - SCENEWIDTH / 2 - 30;
        returnVec.y = rand() % SCENEHEIGHT + (int)playerData.getPos().y - SCENEHEIGHT/2;
    }
    else {
        returnVec.x = (int)playerData.getPos().x + SCENEWIDTH / 2 + 30;
        returnVec.y = rand() % SCENEHEIGHT + (int)playerData.getPos().y - SCENEHEIGHT / 2;
    }
    return returnVec;
}

void PlaySpace::respawnEnemies() {
    int seconds = static_cast<int>(timer.getElapsedTime().asSeconds());
    if (seconds - lastSpawnTime >= 10) {
        lastSpawnTime = seconds;
        for (int i = 0; i < 30; i++) 
            objectsHandler->addEnemy(static_cast<int>(timer.getElapsedTime().asSeconds()/60), randomizePos());
    }
}

void PlaySpace::drawHud() {
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setTextureRect({ {0, 8} , { (int)(((float)playerData.getXp() / playerData.getXpToNext()) * 414), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setTextureRect({ {0, 16} , { (int)(((float)playerData.getCurrentHp() / playerData.getEffectiveHp()) * 200), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 0)->setPosition({ 16 + playerData.getPos().x - 208, 1 + playerData.getPos().y - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setPosition({ 16 + playerData.getPos().x - 208, 1 + playerData.getPos().y - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 2)->setPosition({ 16 + playerData.getPos().x - 208, 10 + playerData.getPos().y - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setPosition({ 16 + playerData.getPos().x - 208, 10 + playerData.getPos().y - 123 });
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

void PlaySpace::chunkLogic() {
    objectsHandler->falseAllChunks();
    for (int dx = -3; dx < 4; dx++)
        for (int dy = -3; dy < 4; dy++)
            objectsHandler->generateChunk((int)playerData.getPos().x / (CHUNKSIZE * TILESIZE) + dx, (int)playerData.getPos().y / (CHUNKSIZE * TILESIZE) + dy);
    objectsHandler->deleteUnusedChunks();
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
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->setPosition({ 208, 124 });
    objectsHandler->loadTextIntoHolder("00:00", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("00:00", 24)) / 2, 11 });
    objectsHandler->loadTextIntoHolder("LVL:1", 9, { SCENEWIDTH/52 - objectsHandler->calculateTextWidth("LVL:1",9)/2 , 0 });
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
    sf::Texture* enemyTexture = objectsHandler->loadTexture({ 24, 32 }, "EnemySprites");
    sf::Texture* projectileTexture = objectsHandler->loadTexture({ 12, 12 }, "ProjectileSprites");
    if (!enemyTexture)
        return true;
    if (!projectileTexture)
        return true;
    playerData.setSizes({ 208, 124 }, { 16, 24 });
    playerData.setMods();
    playerData.setHp((float) playerData.getEffectiveHp());
    return false;
}

void PlaySpace::cleanUp() {
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
    objectsHandler->clearEnemyHolder();
    objectsHandler->clearProjectileHolder();
    objectsHandler->cleanChunkHolder();
    timer.stop();
}

CharacterData PlaySpace::getPlayerData() {
    return playerData;
}

void PlaySpace::movementLogic() {
    sf::Vector2 movement = determineMovement();
    terrainCollision(movement);
}

void PlaySpace::terrainCollision(sf::Vector2f moveStep) {
    int playerChunkX = (int)playerData.getPos().x / (CHUNKSIZE * TILESIZE);
    int playerChunkY = (int)playerData.getPos().y / (CHUNKSIZE * TILESIZE);
    sf::FloatRect playerBounds(
        { playerData.getPos().x,playerData.getPos().y + playerData.getSize().y - playerData.getSize().x },
        { playerData.getSize().x, playerData.getSize().x });
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            auto tempMap = objectsHandler->getChunkMap().at({ playerChunkX + a, playerChunkY + b });
            for (int i = 0; i < CHUNKSIZE; i++) {
                for (int j = 0; j < CHUNKSIZE; j++) {
                    if (tempMap->tiles[i][j].type == 0) {
                        sf::FloatRect tileBounds({
                            (float)(playerChunkX + a) * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)(playerChunkY + b) * TILESIZE * CHUNKSIZE + j * TILESIZE },
                            { (float)TILESIZE, (float)TILESIZE }
                        );
                        if (tileBounds.findIntersection(playerBounds).has_value()) {
                            playerBounds.position.x -= moveStep.x;
                            if (tileBounds.findIntersection(playerBounds).has_value()) {
                                playerBounds.position.x += moveStep.x;
                                playerBounds.position.y -= moveStep.y;
                                if (tileBounds.findIntersection(playerBounds).has_value()) {
                                    playerBounds.position.y += moveStep.y;
                                    playerData.move(-moveStep);
                                    objectsHandler->getSpritePointer(playerHolderIndex, -1)->move(-moveStep);
                                }
                                else {
                                    playerData.move({ 0, -moveStep.y });
                                    objectsHandler->getSpritePointer(playerHolderIndex, -1)->move({ 0, -moveStep.y });
                                }
                            }
                            else {
                                playerData.move({ -moveStep.x, 0 });
                                objectsHandler->getSpritePointer(playerHolderIndex, -1)->move({ -moveStep.x, 0 });
                            }
                        }
                    }
                }
            }
        }
    }
}

sf::Vector2f PlaySpace::determineMovement() {
    float move = playerData.getEffectiveMs();
    sf::Vector2f moveStep = { 0, 0 };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        moveStep.y = move;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        moveStep.y = -move;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        moveStep.x = move;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        moveStep.x = -move;
    playerData.move(moveStep);
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->move(moveStep);
    return moveStep;
}
