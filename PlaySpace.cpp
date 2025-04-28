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
                soundManager->playSound("menuChange", true);
                pauseButtonIndex++;
                if (pauseButtonIndex == 2)
                    pauseButtonIndex = 0;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
                soundManager->playSound("menuChange", true);
                pauseButtonIndex--;
                if (pauseButtonIndex == -1)
                    pauseButtonIndex = 1;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
                soundManager->playSound("menuSelect", true);
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
    objectsHandler->getSpritePointer(pauseMenuHolderIndex, -1)->setPosition({ (float)(50 + (int)playerData.getPos().x - 208), (float)(35 + (int)playerData.getPos().y - 123) });
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonTexture)
        return;
    objectsHandler->loadTextIntoHolder("Resume", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Resume", 24)) / 2, 172 });
    objectsHandler->loadTextIntoHolder("Surrender", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Surrender", 24)) / 2 , 212 });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, pauseMenuHolderIndex);
    objectsHandler->getSpritePointer(pauseMenuHolderIndex, -1)->setPosition({ (float)(171 + (int)playerData.getPos().x - 208), (float)(170 + (int)playerData.getPos().y - 123) });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, pauseMenuHolderIndex);
    objectsHandler->getSpritePointer(pauseMenuHolderIndex, -1)->setPosition({ (float)(171 + (int)playerData.getPos().x - 208), (float)(210 + (int)playerData.getPos().y - 123) });
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
        if (playerData.getCurrentHp() == 0)
            soundManager->playSound("death", false);
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
            soundManager->playSound("death", false);
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
        for (int i = 0; i < 25; i++) 
            objectsHandler->addEnemy(static_cast<int>(timer.getElapsedTime().asSeconds() / 60), randomizePos(), (seconds % 30 == 0 && i == 0) ? true : false);
    }
}

void PlaySpace::setHud() {
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setTextureRect({ {0, 8} , { (int)(((float)playerData.getXp() / playerData.getXpToNext()) * 414), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setTextureRect({ {0, 16} , { (int)(((float)playerData.getCurrentHp() / playerData.getEffectiveMaxHp()) * 200), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 0)->setPosition({ 16.0f + std::round(playerData.getPos().x) - 208, 1 + std::round(playerData.getPos().y) - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setPosition({ 16.0f + std::round(playerData.getPos().x) - 208, 1 + std::round(playerData.getPos().y) - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 2)->setPosition({ 16.0f + std::round(playerData.getPos().x) - 208, 10 + std::round(playerData.getPos().y) - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setPosition({ 16.0f + std::round(playerData.getPos().x) - 208, 10 + std::round(playerData.getPos().y) - 123 });
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
    objectsHandler->getMapGenerator()->falseAllChunks();
    for (int dx = -3; dx < 4; dx++)
        for (int dy = -3; dy < 4; dy++)
            objectsHandler->getMapGenerator()->generateChunk((int)playerData.getPos().x / (CHUNKSIZE * TILESIZE) + dx, (int)playerData.getPos().y / (CHUNKSIZE * TILESIZE) + dy);
    objectsHandler->getMapGenerator()->deleteUnusedChunks();
}

void PlaySpace::setMapAndChar(int readMap, int readChar) {
    mapNumber = readMap;
    charNumber = readChar;
    objectsHandler->setMap(readMap);
}

bool PlaySpace::init() {
    sf::Texture* characterTexture = objectsHandler->loadTexture({ 64, 24 }, "CharacterSprites");
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
    sf::Texture* enemyTexture = objectsHandler->loadTexture({ 80, 48 }, "EnemySprites");
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
    objectsHandler->getMapGenerator()->cleanChunkHolder();
    timer.stop();
}

CharacterData PlaySpace::getPlayerData() {
    return playerData;
}

void PlaySpace::movementLogic() {
    sf::Vector2f movement = determineMovement();
    calculateSlippage(movement);
    terrainCollision(movement);
}

void PlaySpace::calculateSlippage(sf::Vector2f readMovement) {
    sf::Vector2f prevSlippage = playerData.getSlippage();
    prevSlippage /= 1.2f;
    if (prevSlippage.x > 2.0)
        prevSlippage.x = 2;
    else if (prevSlippage.x < -2.0)
        prevSlippage.x = -2;
    if (prevSlippage.y > 2.0)
        prevSlippage.y = 2;
    else if (prevSlippage.y < -2.0)
        prevSlippage.y = -2;
    playerData.setSlippage(prevSlippage);
}

void PlaySpace::terrainCollision(sf::Vector2f moveStep) {
    int playerChunkX = (int)playerData.getPos().x / (CHUNKSIZE * TILESIZE);
    int playerChunkY = (int)playerData.getPos().y / (CHUNKSIZE * TILESIZE);
    sf::FloatRect playerBounds({playerData.getPos().x, playerData.getPos().y + playerData.getSize().y - playerData.getSize().x}, 
            {(float)playerData.getSize().x, (float)playerData.getSize().x});
    bool ifSlip = false;
    moveStep += playerData.getSlippage();
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            auto tempMap = objectsHandler->getMapGenerator()->getChunkMap().at({ playerChunkX + a, playerChunkY + b });
            for (int i = 0; i < CHUNKSIZE; i++) {
                for (int j = 0; j < CHUNKSIZE; j++) {
                    sf::FloatRect tileBounds({ (float)(playerChunkX + a) * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)(playerChunkY + b) * TILESIZE * CHUNKSIZE + j * TILESIZE },
                        { (float)TILESIZE, (float)TILESIZE });
                    if (tempMap->tiles[i][j].type == solid) {
                        playerBounds.position.x += moveStep.x;
                        while (tileBounds.findIntersection(playerBounds).has_value() && std::fabs(moveStep.x) >= 0.05f) {
                            playerBounds.position.x -= moveStep.x;
                            moveStep.x /= 1.4f;
                            if (fabs(moveStep.x) < 0.05f)
                                moveStep.x = 0;
                            playerBounds.position.x += moveStep.x;
                        }
                        playerBounds.position.x -= moveStep.x;
                        playerBounds.position.y += moveStep.y;
                        while (tileBounds.findIntersection(playerBounds).has_value() && std::fabs(moveStep.y) >= 0.05f) {
                            playerBounds.position.y -= moveStep.y;
                            moveStep.y /= 1.4f;
                            if (fabs(moveStep.y) < 0.05f)
                                moveStep.y = 0;
                            playerBounds.position.y += moveStep.y;
                        }
                        playerBounds.position.y -= moveStep.y;
                    }
                    else if (tempMap->tiles[i][j].type == slippery && tileBounds.findIntersection(playerBounds).has_value())
                        ifSlip = true;
                    else if (tempMap->tiles[i][j].type == damaging && tileBounds.findIntersection(playerBounds).has_value())
                        playerData.changeHp(-10);
                }
            }
        }
    }
    if (ifSlip) 
        playerData.setSlippage(playerData.getSlippage() + moveStep * 0.1f);
    else
        playerData.setSlippage({ 0.f, 0.f });
    playerData.move(moveStep);
    objectsHandler->getSpritePointer(playerHolderIndex, -1)->setPosition({ std::round(playerData.getPos().x), std::round(playerData.getPos().y) });
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
    return moveStep;
}

int PlaySpace::getCoins() {
    return static_cast<int>(timer.getElapsedTime().asSeconds());
}

bool PlaySpace::getPaused() {
    return paused;
}