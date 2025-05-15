#include "Engine.h"

Engine::Engine() {
    sceneLabel = MAINMENU;
    soundVolume = 100;
    errorCode = 0;
    selectedMap = 0;
    selectedChar = 0;
    tempVariable = 0;
    scene = nullptr;
}

void Engine::loadVolume() {
    soundManager.loadSounds();
    std::ifstream inFile("Resources/Misc.txt");
    if (inFile) {
        std::string fullscreenStat;
        inFile >> soundVolume;
        inFile.close();
        soundManager.setSoundVolume(soundVolume);
    }
    else 
        soundVolume = 100;
}

void Engine::loadMusic(std::string filename) {
    std::string realFilename = "Resources/Sounds/";
    realFilename = realFilename.append(filename).append(".mp3");
    if (realFilename != currentMusic) {
        playedMusic.stop();
        currentMusic = realFilename;
        playedMusic.openFromFile(realFilename);
        playedMusic.setVolume(soundVolume);
        playedMusic.setLooping(true);
        playedMusic.play();
    }
}

void Engine::mainLoop() {
    loadVolume();
    changeScene();
    loadMusic("MenuMusic");
    while (display.getWindow()->isOpen())
    {
        handleEvents();
        if (errorCode != 0)
            return;
        if (sceneLabel == PLAYSPACE && !(static_cast<PlaySpace*>(scene))->getShouldRun() && (static_cast<PlaySpace*>(scene))->realTimeLogic()) {
            scene->cleanUp();
            tempVariable = (static_cast<PlaySpace*>(scene))->getCoins();
            changeScene();
        }
        draw();
    }
}

void Engine::drawPlayScene(sf::RenderTexture* texture) {
    sf::View camera({ std::round((static_cast<PlaySpace*>(scene))->getPlayerData().getPos().x + 8), std::round((static_cast<PlaySpace*>(scene))->getPlayerData().getPos().y + 12) }, { 432, 270 });
    texture->setView(camera);
    sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.f, camera.getSize());
    for (auto [key, chunk] : objectsHandler.getMapGenerator()->getChunkMap()) {
        sf::Vector2f chunkPos((float)key.first * CHUNKSIZE * TILESIZE, (float)key.second * CHUNKSIZE * TILESIZE);
        if (!viewBounds.findIntersection(sf::FloatRect(chunkPos, sf::Vector2f(CHUNKSIZE * TILESIZE, CHUNKSIZE * TILESIZE))).has_value())
            continue;
        for (int i = 0; i < CHUNKSIZE; i++) {
            for (int j = 0; j < CHUNKSIZE; j++) {
                Tile& tile = chunk->tiles[i][j];
                texture->draw(*tile.sprite);
            }
        }
    }
    for (PowerUp* node : *objectsHandler.getPowerUpHolder()) 
        texture->draw(*node->getSprite());
    for (EnemyData* node : *objectsHandler.getEnemyHolder())
        texture->draw(*node->getSprite());
    for (Projectiles* node : *objectsHandler.getProjectileHolder())
        texture->draw(*node->getSprite());
    (static_cast<PlaySpace*>(scene))->decrementPauseTime();
}

void Engine::draw() {
    display.getWindow()->clear();
    static sf::RenderTexture renderTexture({ 432, 270 });
    renderTexture.clear();
    renderTexture.setView(renderTexture.getDefaultView());
    if (sceneLabel == PLAYSPACE) 
        drawPlayScene(&renderTexture);
    for (std::vector<sf::Sprite>* var : *objectsHandler.getSpriteHolder()) 
        for (sf::Sprite& sprite : *var)
            renderTexture.draw(sprite);
    renderTexture.display();
    sf::Sprite finalSprite(renderTexture.getTexture());
    finalSprite.setScale({display.getWindowSize().x/ 432.0f,display.getWindowSize().y / 270.f });
    display.getWindow()->draw(finalSprite);
    for (sf::Text text : *objectsHandler.getTextHolder())
    {
        sf::Text copy = text;
        copy.setPosition({ copy.getPosition().x * display.getWindowSize().x / 432.0f, copy.getPosition().y * display.getWindowSize().y / 270.f });
        copy.setCharacterSize(copy.getCharacterSize() * (unsigned int)display.getWindowSize().y / 270);
        display.getWindow()->draw(copy);
    }
    display.getWindow()->display();
}

void Engine::handleEvents() {
    if (display.getWindow()->hasFocus()) {
        SceneLabels temp = sceneLabel;
        while (std::optional event = display.getWindow()->pollEvent()) {
            if (scene->eventLogic(event)) {
                scene->cleanUp();
                if (temp != sceneLabel) 
                    changeScene();
                else {
                    sceneLabel = MAINMENU;
                    display.getWindow()->close();
                }
                break;
            };
        }
    }
}

void Engine::changeScene() {
    delete scene;
    switch (sceneLabel) {
        case MAINMENU:
            loadMusic("MenuMusic");
            scene = new MainMenu(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            break;
        case SETTINGS:
            scene = new SettingsScene(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            (static_cast<SettingsScene*>(scene))->setDisplay(&display);
            (static_cast<SettingsScene*>(scene))->setMusicPointer(&playedMusic);
            break;
        case GALLERY:
            scene = new GalleryScene(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            break;
        case RESETCHOICE:
            scene = new ResetChoice(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            (static_cast<ResetChoice*>(scene))->setDisplay(&display);
            break;
        case UPGRADE:
            scene = new UpgradeScene(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            (static_cast<UpgradeScene*>(scene))->loadModifiers();
            break;
        case PLAYCHOICE:
            scene = new PlayChoice(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            (static_cast<PlayChoice*>(scene))->setPointers(&selectedMap, &selectedChar);
            break;
        case PLAYSPACE:
            scene = new PlaySpace(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            (static_cast<PlaySpace*>(scene))->setMapAndChar(selectedMap, selectedChar);
            loadMusic(std::string("MusicMap").append(std::to_string(selectedMap + 1)));
            break;
        case FINISHSCREEN:
            scene = new FinishScreen(&objectsHandler, &sceneLabel, &soundManager, &soundVolume);
            (static_cast<FinishScreen*>(scene))->setCoins(tempVariable, selectedMap, selectedChar);
            tempVariable = 0;
            break;
    }
    if (scene->init()) 
        errorCode = (int)sceneLabel;
}

int Engine::getErrorCode() {
    return errorCode;
}
