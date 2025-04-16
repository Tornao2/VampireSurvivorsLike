    #include "PlaySpace.h"

bool PlaySpace::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>()) 
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape && pauseBreak == 0) {
            paused = !paused;
            pauseBreak = 10;
            if (paused) {
                timer.stop();
                initPauseMenu();
            }
            else {
                timer.start();
                cleanPauseMenu();
            }
        }
        else if (paused) {
            if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
                pauseButtonIndex++;
                if (pauseButtonIndex == 2)
                    pauseButtonIndex = 0;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
                pauseButtonIndex--;
                if (pauseButtonIndex == -1)
                    pauseButtonIndex = 1;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
                if (pauseButtonIndex == 0) {
                    paused = !paused;
                    pauseBreak = 10;
                    timer.start();
                    cleanPauseMenu();
                    return false;
                }
                else {
                    *sceneLabel = MAINMENU;
                    return true;
                }
            }
            pauseButtonFocus();
        }
    }
    return false;
}

void PlaySpace::cleanPauseMenu() {
    objectsHandler->getSpriteHolder()->at(pauseMenuHolderIndex)->clear();
    delete objectsHandler->getSpriteHolder()->at(pauseMenuHolderIndex);
    objectsHandler->getSpriteHolder()->erase(objectsHandler->getSpriteHolder()->end()-1);
    pauseMenuHolderIndex = 0;
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1); 
}

void PlaySpace::initPauseMenu() {
    pauseButtonIndex = 0;
    sf::Texture* pauseBgTexture = objectsHandler->loadTexture({ 332, 220 }, "PauseBackground");
    if (!pauseBgTexture)
        return;
    pauseMenuHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*pauseBgTexture, { 332,220 }, { 0, 0 }, pauseMenuHolderIndex);
    objectsHandler->getSpritePointer(pauseMenuHolderIndex, -1)->setPosition({ 50 + playerData.getPos().x - 208, 35 + playerData.getPos().y - 123 });
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonTexture)
        return;
    objectsHandler->loadTextIntoHolder("Resume", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Resume", 24)) / 2, 172 });
    objectsHandler->loadTextIntoHolder("Surrender", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Surrender", 24)) / 2 , 212 });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, pauseMenuHolderIndex);
    objectsHandler->getSpritePointer(pauseMenuHolderIndex, -1)->setPosition({ 171 + playerData.getPos().x - 208, 170 + playerData.getPos().y - 123 });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, pauseMenuHolderIndex);
    objectsHandler->getSpritePointer(pauseMenuHolderIndex, -1)->setPosition({ 171 + playerData.getPos().x - 208, 210 + playerData.getPos().y - 123 });
    pauseButtonFocus();
}

void PlaySpace::pauseButtonFocus() {
    (*objectsHandler->getTextHolder())[objectsHandler->getTextHolder()->size() - 2].setFillColor(sf::Color::White);
    (*objectsHandler->getTextHolder())[objectsHandler->getTextHolder()->size() - 1].setFillColor(sf::Color::White);
    (*objectsHandler->getTextHolder())[objectsHandler->getTextHolder()->size() - 2 + pauseButtonIndex].setFillColor(GREEN);
}

void PlaySpace::decrementPauseTime() {
    pauseBreak = (pauseBreak == 0) ? 0 : pauseBreak - 1;
}

bool PlaySpace::realTimeLogic() {
    int seconds = static_cast<int>(timer.getElapsedTime().asSeconds());
    if (playerData.getCurrentHp() == 0 || seconds >= 600) {
        *sceneLabel = FINISHSCREEN;
        return true;
    }
    else {
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
        setHud();
        respawnEnemies();
        return false;
    }
}

void PlaySpace::weaponLogic() {
    if (objectsHandler->getEnemyHolder()->size() != 0) {
        sf::Vector2f target = objectsHandler->getClosestEnemyCords(playerData.getPos());
        if (static_cast<int>(timer.getElapsedTime().asSeconds()) - lastFireTime > 1) {
            lastFireTime = static_cast<int>(timer.getElapsedTime().asSeconds());
            objectsHandler->addProjectile(playerData.getEffectiveDamage(), 0, playerData.getPos(), target);
        }
    }
}

void PlaySpace::moveProjectiles() {
    std::list <Projectiles*> proj;
    for (Projectiles* node : *objectsHandler->getProjectileHolder()) {
        node->move();
        if ((node->getPos() - playerData.getPos()).length() >= 400)
            proj.push_back(node);
    }
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
    std::list <EnemyData*> enemiesToKill;
    for (EnemyData* enemy : *objectsHandler->getEnemyHolder()) {
        sf::Vector2f dirVec = playerData.getPos() - enemy->getPos();
        float length = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
        if (fabs(length) >= 0.5) {
            dirVec /= length;
            enemy->move(dirVec);
        }
        if ((enemy->getPos() - playerData.getPos()).length() >= 400) {
            if (enemy->getIfBoss()) {
                sf::Vector2f getDifference = (playerData.getPos() - enemy->getPos())/1.5f;
                enemy->setPosition(playerData.getPos() + getDifference);
            }
            else 
                enemiesToKill.push_back(enemy);
        }
    }
    objectsHandler->killEnemy(enemiesToKill);
}

void PlaySpace::checkEnemyCollision() {
    sf::FloatRect playerBounds({ playerData.getPos().x,playerData.getPos().y + playerData.getSize().y - playerData.getSize().x }, { (float) playerData.getSize().x, (float) playerData.getSize().x});
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
    if (seconds - lastSpawnTime >= 3) {
        lastSpawnTime = seconds;
        for (int i = 0; i < 10; i++) 
            objectsHandler->addEnemy(static_cast<int>(timer.getElapsedTime().asSeconds() / 60), randomizePos(), (seconds % 30 == 0 && i == 0) ? true : false);
    }
}

void PlaySpace::setHud() {
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setTextureRect({ {0, 8} , { (int)(((float)playerData.getXp() / playerData.getXpToNext()) * 414), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setTextureRect({ {0, 16} , { (int)(((float)playerData.getCurrentHp() / playerData.getEffectiveMaxHp()) * 200), 8} });
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
    sf::Texture* characterTexture = objectsHandler->loadTexture({ 32, 24 }, "CharacterSprites");
    if (!characterTexture)
        return true;
    playerData.setSizes({ 208, 124 }, { 16, 24 });
    playerData.setMods();
    playerData.setBaseStats(charNumber);
    playerData.setHp(playerData.getEffectiveMaxHp());
    playerHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*characterTexture, playerData.getSize(), playerData.getOffsets(), playerHolderIndex);
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
    sf::FloatRect playerBounds({ playerData.getPos().x,playerData.getPos().y + playerData.getSize().y - playerData.getSize().x }, { (float) playerData.getSize().x, (float) playerData.getSize().x });
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

int PlaySpace::getCoins() {
    return static_cast<int>(timer.getElapsedTime().asSeconds());
}

bool PlaySpace::getPaused() {
    return paused;
}