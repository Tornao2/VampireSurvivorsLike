#include "Engine.h"

Engine::Engine() {
	sceneLabel = MAINMENU;
}

void Engine::mainLoop() {
    if (objectsHandler.loadFont()) {
        errorCode = -1;
        return;
    }
    scene = new MainMenu(&objectsHandler, &sceneLabel);
    changeScene();
    while (display.getWindow()->isOpen())
    {
        handleEvents();
        if (sceneLabel == PLAYSPACE) 
            if ((static_cast<PlaySpace*>(scene))->realTimeLogic()) 
                errorCode = -2;
        draw();
        if (errorCode != 0) 
            return;
    }
}

void Engine::drawPlayScene(sf::RenderTexture* texture) {
    sf::View camera({ (static_cast<PlaySpace*>(scene))->getPlayerData().getX() + 8, (static_cast<PlaySpace*>(scene))->getPlayerData().getY() + 12 }, { 432, 270 });
    texture->setView(camera);
    sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.f, camera.getSize());
    for (auto [key, chunk] : objectsHandler.getChunkMap()) {
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
    for (EnemyData* node : *objectsHandler.getEnemyHolder())
        texture->draw(*node->getEnemyDataNode()->sprite);
}

void Engine::draw() {
    display.getWindow()->clear();
    static sf::RenderTexture renderTexture({ 432, 270 });
    renderTexture.clear();
    if (sceneLabel == PLAYSPACE) 
        drawPlayScene(&renderTexture);
    for (std::vector<sf::Sprite>* var : *objectsHandler.getSpriteHolder()) 
        for (sf::Sprite& sprite : *var) 
            renderTexture.draw(sprite);
    renderTexture.display();
    sf::Sprite finalSprite(renderTexture.getTexture());
    finalSprite.setScale({display.getWindowWidth()/ 432.0f,display.getWindowHeight() / 270.f });
    display.getWindow()->draw(finalSprite);
    for (sf::Text text : *objectsHandler.getTextHolder())
    {
        sf::Text copy = text;
        copy.setPosition({ copy.getPosition().x * display.getWindowWidth() / 432.0f, copy.getPosition().y * display.getWindowHeight() / 270.f });
        copy.setCharacterSize(copy.getCharacterSize() * (unsigned int) display.getWindowHeight() / 270);
        display.getWindow()->draw(copy);
    }
    display.getWindow()->display();
}

void Engine::handleEvents() {
    if (display.getWindow()->hasFocus()) {
        SceneLabels temp = sceneLabel;
        while (std::optional event = display.getWindow()->pollEvent()) {
            if (scene->logic(event)) {
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
    switch (sceneLabel) {
        case MAINMENU:
            scene = new MainMenu(&objectsHandler, &sceneLabel);
            break;
        case SETTINGS:
            scene = new SettingsScene(&objectsHandler, &sceneLabel);
            (static_cast<SettingsScene*>(scene))->setDisplay(&display);
            break;
        case RESETCHOICE:
            scene = new ResetChoice(&objectsHandler, &sceneLabel);
            (static_cast<ResetChoice*>(scene))->setDisplay(&display);
            break;
        case UPGRADE:
            scene = new UpgradeScene(&objectsHandler, &sceneLabel);
            (static_cast<UpgradeScene*>(scene))->loadModifiers();
            break;
        case PLAYCHOICE:
            scene = new PlayChoice(&objectsHandler, &sceneLabel);
            (static_cast<PlayChoice*>(scene))->setPointers(&selectedMap, &selectedChar);
            break;
        case GALLERY:
            break;
        case PLAYSPACE:
            scene = new PlaySpace(&objectsHandler, &sceneLabel);
            (static_cast<PlaySpace*>(scene))->setMapAndChar(selectedMap, selectedChar);
            break;
    }
    if (scene->init()) 
        errorCode = (int)sceneLabel;
}

int Engine::getErrorCode() {
    return errorCode;
}