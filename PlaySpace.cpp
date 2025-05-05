    #include "PlaySpace.h"

bool PlaySpace::eventLogic(std::optional<sf::Event> gameEvent) {
    if (gameEvent->is<sf::Event::Closed>())
        return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape && levelingUp == 0 && pauseBreak == 0) {
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
                buttonIndex++;
                if (buttonIndex == 2)
                    buttonIndex = 0;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
                soundManager->playSound("menuChange", true);
                buttonIndex--;
                if (buttonIndex == -1)
                    buttonIndex = 1;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
                soundManager->playSound("menuSelect", true);
                if (buttonIndex == 0) {
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
        else if (levelingUp) {
            if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
                soundManager->playSound("menuChange", true);
                buttonIndex++;
                if (buttonIndex >= availableChoices)
                    buttonIndex = 0;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
                soundManager->playSound("menuChange", true);
                buttonIndex--;
                if (buttonIndex < 0)
                    buttonIndex = availableChoices - 1;
            }
            else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
                soundManager->playSound("menuSelect", true);
                if (buttonIndex == 0) {
                    if (weaponTaking) 
                        playerData.addWeapon(choiceAId, std::stoi(std::string(objectsHandler->getTextPointer(2)->getString())), objectsHandler->loadTexture({ 51, 21 }, "ProjectileSprites"));
                    else 
                        playerData.addItem(choiceAId, std::stoi(std::string(objectsHandler->getTextPointer(2)->getString())));
                }
                else {
                    if (weaponTaking) 
                        playerData.addWeapon(choiceBId, std::stoi(std::string(objectsHandler->getTextPointer(5)->getString())), objectsHandler->loadTexture({ 51, 21 }, "ProjectileSprites"));
                    else 
                        playerData.addItem(choiceBId, std::stoi(std::string(objectsHandler->getTextPointer(5)->getString())));
                }
                levelingUp = false;
                levelDifference--;
                timer.start();
                cleanLevelMenu();
                return false;
            }
            levelButtonFocus();
        }
    }
    return false;
}

void PlaySpace::cleanPauseMenu() {
    objectsHandler->getSpriteHolder()->at(additionalMenuIndex)->clear();
    delete objectsHandler->getSpriteHolder()->at(additionalMenuIndex);
    objectsHandler->getSpriteHolder()->erase(objectsHandler->getSpriteHolder()->end()-1);
    additionalMenuIndex = 0;
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1); 
    int temp = playerData.getHowManyItem();
    for (int i = 0; i < temp; i++) {
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    }
    temp = playerData.getHowManyWeapons();
    for (int i = 0; i < temp; i++) {
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    }
}

void PlaySpace::initPauseMenu() {
    buttonIndex = 0;
    sf::Texture* pauseBgTexture = objectsHandler->loadTexture({ 332, 220 }, "PauseBackground");
    if (!pauseBgTexture)
        return;
    additionalMenuIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*pauseBgTexture, { 332,220 }, { 0, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(50 + (int)playerData.getPos().x - 208), (float)(35 + (int)playerData.getPos().y - 123) });
    sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
    if (!buttonTexture)
        return;
    objectsHandler->loadTextIntoHolder("Resume", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Resume", 24)) / 2, 172 });
    objectsHandler->loadTextIntoHolder("Surrender", 24, { (SCENEWIDTH - objectsHandler->calculateTextWidth("Surrender", 24)) / 2 , 212 });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(171 + (int)playerData.getPos().x - 208), (float)(170 + (int)playerData.getPos().y - 123) });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(171 + (int)playerData.getPos().x - 208), (float)(210 + (int)playerData.getPos().y - 123) });
    objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(171 + (int)playerData.getPos().x - 208), (float)(210 + (int)playerData.getPos().y - 123) });
    sf::Texture* levelUpTexture = objectsHandler->loadTexture({ 290, 128 }, "LevelUpBackground");
    if (!levelUpTexture)
        return;
    std::vector<Weapon>* weapons = playerData.getWeaponInfo();
    sf::Texture* weaponTextures = objectsHandler->loadTexture({ 160, 62 }, "WeaponSprites");
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(95 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
    if ((*weapons)[0].getBasicInfo()->currentLevel != 0) {
        objectsHandler->loadSpriteIntoHolder(*weaponTextures, { 32,31 }, { (((*weapons)[0].getBasicInfo()->itemId - 6) % 5) * 32 , (((*weapons)[0]).getBasicInfo()->itemId - 6) / 5 * 31 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(95 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadTextIntoHolder(std::to_string((*weapons)[0].getBasicInfo()->currentLevel), 15, { 100 , 118 });
        objectsHandler->loadTextIntoHolder(std::to_string((*weapons)[0].getBasicInfo()->maxLevel), 15, { 119 , 118 });
    }
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(137 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
    if ((*weapons)[1].getBasicInfo()->currentLevel != 0) {
        objectsHandler->loadSpriteIntoHolder(*weaponTextures, { 32,31 }, { (((*weapons)[1].getBasicInfo()->itemId - 6) % 5) * 32 , (((*weapons)[1]).getBasicInfo()->itemId - 6) / 5 * 31 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(137 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadTextIntoHolder(std::to_string((*weapons)[1].getBasicInfo()->currentLevel), 15, { 142 , 118 });
        objectsHandler->loadTextIntoHolder(std::to_string((*weapons)[1].getBasicInfo()->maxLevel), 15, { 161 , 118 });
    }
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(179 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
    if ((*weapons)[2].getBasicInfo()->currentLevel != 0) {
        objectsHandler->loadSpriteIntoHolder(*weaponTextures, { 32,31 }, { (((*weapons)[2].getBasicInfo()->itemId - 6) % 5) * 32 , (((*weapons)[2]).getBasicInfo()->itemId - 6) / 5 * 31 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(179 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadTextIntoHolder(std::to_string((*weapons)[2].getBasicInfo()->currentLevel), 15, { 184 , 118 });
        objectsHandler->loadTextIntoHolder(std::to_string((*weapons)[2].getBasicInfo()->maxLevel), 15, { 203 , 118 });
    }
    std::vector<ItemInfo>* infos = playerData.getItemIds();
    sf::Texture* itemTextures = objectsHandler->loadTexture({ 96, 62 }, "itemSprites");
    if (!itemTextures)
        return;
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(221 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
    if ((*infos)[0].currentLevel != 0) {
        objectsHandler->loadSpriteIntoHolder(*itemTextures, { 32,31 },  {(((*infos)[0].itemId - 1) % 3) * 32 , ((*infos)[0].itemId - 1) / 3 * 31}, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(221 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadTextIntoHolder(std::to_string((*infos)[0].currentLevel), 15, { 226 , 118});
        objectsHandler->loadTextIntoHolder(std::to_string((*infos)[0].maxLevel), 15, { 245 , 118 });
    }
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(263 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
    if ((*infos)[1].currentLevel != 0) {
        objectsHandler->loadSpriteIntoHolder(*itemTextures, { 32,31 }, { (((*infos)[1].itemId -1) % 3) * 32 , ((*infos)[1].itemId - 1) / 3 * 31}, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(263 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadTextIntoHolder(std::to_string((*infos)[1].currentLevel), 15, { 268 , 118 });
        objectsHandler->loadTextIntoHolder(std::to_string((*infos)[1].maxLevel), 15, { 287 , 118 });
    }
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(305 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
    if ((*infos)[2].currentLevel != 0) {
        objectsHandler->loadSpriteIntoHolder(*itemTextures, { 32,31 }, { (((*infos)[2].itemId - 1) % 3) * 32 , ((*infos)[2].itemId - 1) / 3 * 31 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(305 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadTextIntoHolder(std::to_string((*infos)[2].currentLevel), 15, { 310 , 118 });
        objectsHandler->loadTextIntoHolder(std::to_string((*infos)[2].maxLevel), 15, { 329 , 118 });
    }
    pauseButtonFocus();
}

bool PlaySpace::getItemOrWeapon() {
    int usedWSlots = playerData.getUsedWeaponSlots();
    int usedISlots = playerData.getUsedItemSlots();
    if (rand() % 2) {
        availableChoices = 3 - usedWSlots;
        if (availableChoices != 0)
            weaponTaking = true;
        else {
            availableChoices = 3 - usedISlots;
            if (availableChoices != 0)
                weaponTaking = false;
            else
                return false;
        }
    }
    else {
        availableChoices = 3 - usedISlots;
        if (availableChoices != 0)
            weaponTaking = false;
        else {
            availableChoices = 3 - usedWSlots;
            if (availableChoices != 0)
                weaponTaking = true;
            else
                return false;
        }
    }
    if (availableChoices > 2)
        availableChoices = 2;
    return true;
}

bool PlaySpace::initLevelUp() {
    if (!getItemOrWeapon())
        return false;
    buttonIndex = 0;
    sf::Texture* levelUpTexture = objectsHandler->loadTexture({ 290, 128 }, "LevelUpBackground");
    if (!levelUpTexture)
        return false;
    additionalMenuIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 193,128 }, { 0, 0 }, additionalMenuIndex);
    objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(119 + (int)playerData.getPos().x - 208), (float)(71 + (int)playerData.getPos().y - 123) });
    sf::Texture* itemTextures = objectsHandler->loadTexture({ 96, 62 }, "ItemSprites");
    sf::Texture* weaponTextures = objectsHandler->loadTexture({ 160, 62 }, "WeaponSprites");
    std::vector<std::tuple<int, int, int>> itemIds;
    bool found = false;
    if (!itemTextures)
        return false;
    if (!weaponTextures)
        return false;
    if (availableChoices == 2) {
        objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 65,110 }, { 193, 0 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(148 + (int)playerData.getPos().x - 208), (float)(80 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 65,110 }, { 193, 0 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(220 + (int)playerData.getPos().x - 208), (float)(80 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(164 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(236 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        if (weaponTaking) {
            std::vector<Weapon>* infos = playerData.getWeaponInfo();
            for (Weapon item : *infos)
                if (item.getBasicInfo()->maxLevel != -1)
                    itemIds.push_back({ item.getBasicInfo()->itemId, item.getBasicInfo()->currentLevel, item.getBasicInfo()->maxLevel });
            while (itemIds.size() != (3 - playerData.getUsedWeaponSlots())) {
                int temp = (rand() % 5) + 6;
                for (Weapon item : *infos)
                    if (temp == item.getBasicInfo()->itemId) {
                        found = true;
                        break;
                    }
                for (auto& tup : itemIds)
                    if (std::get<0>(tup) == temp) {
                        found = true;
                        break;
                    }
                if (!found)
                    itemIds.push_back({ temp, 0, 5 });
                found = false;
            }
            for (int i = itemIds.size() - 1; i > 0; --i) {
                int j = std::rand() % (i + 1);
                std::swap(itemIds[i], itemIds[j]);
            }
            choiceAId = std::rand() % itemIds.size(), choiceBId = std::rand() % itemIds.size();
            while (choiceBId == choiceAId)
                choiceBId = std::rand() % itemIds.size();
            objectsHandler->loadSpriteIntoHolder(*weaponTextures, { 32,31 }, { ((std::get<0>(itemIds[choiceAId]) - 1) % 5) * 32 , 0 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(164 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadSpriteIntoHolder(*weaponTextures, { 32,31 }, { ((std::get<0>(itemIds[choiceBId]) - 1) % 5) * 32 , 0 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(236 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<1>(itemIds[choiceAId]) + 1)), 15, { 169 , 118 });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<2>(itemIds[choiceAId]))), 15, { 188 , 118 });
            objectsHandler->loadTextIntoHolder(getUpgradeText(std::get<0>(itemIds[choiceAId]), std::get<1>(itemIds[choiceAId]) + 1), 11, { 149 , 134 });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<1>(itemIds[choiceBId]) + 1)), 15, { 241 , 118 });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<2>(itemIds[choiceBId]))), 15, { 260 , 118 });
            objectsHandler->loadTextIntoHolder(getUpgradeText(std::get<0>(itemIds[choiceBId]), std::get<1>(itemIds[choiceBId]) + 1), 11, { 221 , 134 });
            choiceAId = std::get<0>(itemIds[choiceAId]);
            choiceBId = std::get<0>(itemIds[choiceBId]);
        }
        else {
            std::vector<ItemInfo>* infos = playerData.getItemIds();
            for (ItemInfo item : *infos) 
                if (item.maxLevel != -1)
                    itemIds.push_back({ item.itemId, item.currentLevel, item.maxLevel }); 
            while (itemIds.size() != (3 - playerData.getUsedItemSlots())) {
                int temp = (rand() % 5) + 1;
                for (ItemInfo item : *infos)
                    if (temp == item.itemId) {
                        found = true;
                        break;
                    }
                for (auto& tup : itemIds)
                    if (std::get<0>(tup) == temp) {
                        found = true;
                        break;
                    }
                if (!found)
                    itemIds.push_back({ temp, 0, 5 });
                found = false;
            }
            for (int i = itemIds.size() - 1; i > 0; --i) {
                int j = std::rand() % (i + 1);
                std::swap(itemIds[i], itemIds[j]);
            }
            choiceAId = std::rand() % itemIds.size(), choiceBId = std::rand() % itemIds.size();
            while (choiceBId == choiceAId)
                choiceBId = std::rand() % itemIds.size();
            objectsHandler->loadSpriteIntoHolder(*itemTextures, { 32,31 }, { ((std::get<0>(itemIds[choiceAId]) - 1) % 3) * 32 , (std::get<0>(itemIds[choiceAId]) - 1)/3 * 31 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(164 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadSpriteIntoHolder(*itemTextures, { 32,31 }, { ((std::get<0>(itemIds[choiceBId]) - 1) % 3) * 32 , (std::get<0>(itemIds[choiceBId]) - 1) / 3 * 31 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(236 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<1>(itemIds[choiceAId]) + 1)), 15, { 169 , 118 });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<2>(itemIds[choiceAId]))), 15, { 188 , 118 });
            objectsHandler->loadTextIntoHolder(getUpgradeText(std::get<0>(itemIds[choiceAId]), std::get<1>(itemIds[choiceAId]) + 1), 11, { 149 , 134 });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<1>(itemIds[choiceBId]) + 1)), 15, { 241 , 118 });
            objectsHandler->loadTextIntoHolder(std::to_string((std::get<2>(itemIds[choiceBId]))), 15, { 260 , 118 });
            objectsHandler->loadTextIntoHolder(getUpgradeText(std::get<0>(itemIds[choiceBId]), std::get<1>(itemIds[choiceBId]) + 1), 11, { 221 , 134 });
            choiceAId = std::get<0>(itemIds[choiceAId]);
            choiceBId = std::get<0>(itemIds[choiceBId]);
        }
    }
    else {
        objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 65,110 }, { 193, 0 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(183 + (int)playerData.getPos().x - 208), (float)(80 + (int)playerData.getPos().y - 123) });
        objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
        objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(199 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
        if (weaponTaking) {
            objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 65,110 }, { 193, 0 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(148 + (int)playerData.getPos().x - 208), (float)(80 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 65,110 }, { 193, 0 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(220 + (int)playerData.getPos().x - 208), (float)(80 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(164 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
            objectsHandler->loadSpriteIntoHolder(*levelUpTexture, { 32,47 }, { 258, 0 }, additionalMenuIndex);
            objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(236 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
            if (weaponTaking) {
                std::vector<Weapon>* infos = playerData.getWeaponInfo();
                for (Weapon item : *infos)
                    if (item.getBasicInfo()->maxLevel != -1)
                        itemIds.push_back({ item.getBasicInfo()->itemId, item.getBasicInfo()->currentLevel, item.getBasicInfo()->maxLevel });
                while (itemIds.size() != (3 - playerData.getUsedWeaponSlots())) {
                    int temp = (rand() % 5) + 6;
                    for (Weapon item : *infos)
                        if (temp == item.getBasicInfo()->itemId) {
                            found = true;
                            break;
                        }
                    for (auto& tup : itemIds)
                        if (std::get<0>(tup) == temp) {
                            found = true;
                            break;
                        }
                    if (!found)
                        itemIds.push_back({ temp, 0, 5 });
                    found = false;
                }
                for (int i = itemIds.size() - 1; i > 0; --i) {
                    int j = std::rand() % (i + 1);
                    std::swap(itemIds[i], itemIds[j]);
                }
                choiceAId = std::rand() % itemIds.size();
                objectsHandler->loadSpriteIntoHolder(*weaponTextures, { 32,31 }, { ((std::get<0>(itemIds[choiceAId]) - 1) % 5) * 32 , 0 }, additionalMenuIndex);
                objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(199 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
                objectsHandler->loadTextIntoHolder(std::to_string((std::get<1>(itemIds[choiceAId]) + 1)), 15, { 204 , 118 });
                objectsHandler->loadTextIntoHolder(std::to_string((std::get<2>(itemIds[choiceAId]))), 15, { 223 , 118 });
                objectsHandler->loadTextIntoHolder(getUpgradeText(std::get<0>(itemIds[choiceAId]), std::get<1>(itemIds[choiceAId]) + 1), 11, { 184 , 134 });
                choiceAId = std::get<0>(itemIds[choiceAId]);
            }
            else {
                std::vector<ItemInfo>* infos = playerData.getItemIds();
                for (ItemInfo item : *infos)
                    if (item.maxLevel != -1)
                        itemIds.push_back({ item.itemId, item.currentLevel, item.maxLevel });
                while (itemIds.size() != (3 - playerData.getUsedItemSlots())) {
                    int temp = (rand() % 5) + 1;
                    for (ItemInfo item : *infos)
                        if (temp == item.itemId) {
                            found = true;
                            break;
                        }
                    for (auto& tup : itemIds)
                        if (std::get<0>(tup) == temp) {
                            found = true;
                            break;
                        }
                    if (!found)
                        itemIds.push_back({ temp, 0, 5 });
                    found = false;
                }
                for (int i = itemIds.size() - 1; i > 0; --i) {
                    int j = std::rand() % (i + 1);
                    std::swap(itemIds[i], itemIds[j]);
                }
                choiceAId = std::rand() % itemIds.size();
                objectsHandler->loadSpriteIntoHolder(*itemTextures, { 32,31 }, { ((std::get<0>(itemIds[choiceAId]) - 1) % 3) * 32 , (std::get<0>(itemIds[choiceAId]) - 1) / 3 * 31 }, additionalMenuIndex);
                objectsHandler->getSpritePointer(additionalMenuIndex, -1)->setPosition({ (float)(199 + (int)playerData.getPos().x - 208), (float)(88 + (int)playerData.getPos().y - 123) });
                objectsHandler->loadTextIntoHolder(std::to_string((std::get<1>(itemIds[choiceAId]) + 1)), 15, { 204 , 118 });
                objectsHandler->loadTextIntoHolder(std::to_string((std::get<2>(itemIds[choiceAId]))), 15, { 223 , 118 });
                objectsHandler->loadTextIntoHolder(getUpgradeText(std::get<0>(itemIds[choiceAId]), std::get<1>(itemIds[choiceAId]) + 1), 11, { 184 , 134 });
                choiceAId = std::get<0>(itemIds[choiceAId]);
            }
        }
    }
    levelButtonFocus();
    return true;
}

void PlaySpace::cleanLevelMenu() {
    objectsHandler->getSpriteHolder()->at(additionalMenuIndex)->clear();
    delete objectsHandler->getSpriteHolder()->at(additionalMenuIndex);
    objectsHandler->getSpriteHolder()->erase(objectsHandler->getSpriteHolder()->end() - 1);
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    if (availableChoices == 2) {
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
        objectsHandler->getTextHolder()->erase(objectsHandler->getTextHolder()->end() - 1);
    }
    additionalMenuIndex = 0;
}

void PlaySpace::pauseButtonFocus() {
    for (sf::Text& text : *objectsHandler->getTextHolder())
        text.setFillColor(sf::Color::White);
    (*objectsHandler->getTextHolder())[buttonIndex+2].setFillColor(GREEN);
}

void PlaySpace::levelButtonFocus() {
    for (sf::Sprite& sprite : *(*objectsHandler->getSpriteHolder()).at(additionalMenuIndex)) 
        sprite.setColor(sf::Color::White);
    (*objectsHandler->getSpriteHolder()).at(additionalMenuIndex)->at(1 + buttonIndex).setColor(GREEN);
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
        if (levelDifference) {
            levelingUp = true;
            timer.stop();
            if (!initLevelUp()) {
                levelingUp = false;
                timer.start();
            } else 
                return false;
        }
        int prevLevel = playerData.getLevel();
        playerData.decrementInvincibility();
        chunkLogic();
        movementLogic();
        powerUpLogic();
        moveEnemies();
        weaponLogic();
        moveProjectiles();
        checkProjectileCollision();
        checkEnemyHp();
        checkEnemyCollision();
        setTimer();
        setHud();
        respawnEnemies();  
        if (prevLevel != playerData.getLevel())           
            levelDifference = playerData.getLevel() - prevLevel;
        return false;
    }
}

void PlaySpace::powerUpLogic() {
    sf::FloatRect playerBounds({ playerData.getPos().x,playerData.getPos().y + playerData.getSize().y - playerData.getSize().x }, { (float)playerData.getSize().x, (float)playerData.getSize().x });
    for (PowerUp* powerUp : *objectsHandler->getPowerUpHolder()) {
        sf::FloatRect powerUpBounds(powerUp->getPos(), { (float) powerUp->getSize().x,(float) powerUp->getSize().y });
        if (powerUp->decrementTimeLeft()) {
            objectsHandler->destroyPowerUp(powerUp);
            return;
        }
        else if (playerBounds.findIntersection(powerUpBounds).has_value()) {
            usePowerUp(powerUp->getId());
            objectsHandler->destroyPowerUp(powerUp);
            return;
        }
    }
}

void PlaySpace::usePowerUp(int readId) {
    std::list <EnemyData*> enemiesToKill = *objectsHandler->getEnemyHolder();
    switch (readId) {
        case 0:
            additionalCoins += 50;
            soundManager->playSound("powerCoin", false);
            break;
        case 1:      
            objectsHandler->killEnemy(enemiesToKill);
            soundManager->playSound("powerBomb", false);
            break;
        case 2:
            playerData.setHp(playerData.getEffectiveMaxHp());
            soundManager->playSound("powerHp", false);
            break;
        case 3:
            playerData.increaseXp((200 * playerData.getLevel())/5);
            soundManager->playSound("powerXp", false);
            objectsHandler->getTextPointer(1)->setString(std::string("LVL:").append(std::to_string(playerData.getLevel())));
            break;
    }
}

void PlaySpace::weaponLogic() {
    if (objectsHandler->getEnemyHolder()->size() != 0) {
        sf::Vector2f target = objectsHandler->getClosestEnemyCords(playerData.getPos());
        //if (static_cast<int>(timer.getElapsedTime().asSeconds()) - lastFireTime > 1) {
            lastFireTime = static_cast<int>(timer.getElapsedTime().asSeconds());
            objectsHandler->addProjectile(playerData.getEffectiveDamage(), 0, playerData.getPos(), target);
        //}
    }
}

void PlaySpace::moveProjectiles() {
    std::list <Projectiles*> proj;
    for (Projectiles* node : *objectsHandler->getProjectileHolder()) {
        node->move();
        if ((node->getPos() - playerData.getPos()).length() >= 500)
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
            if (enemy->getIfBoss())
                objectsHandler->addPowerUp(rand()%4, enemy->getPos());
        }
    }
    objectsHandler->killEnemy(enemiesToKill);
}

void PlaySpace::moveEnemies() {
    std::list <EnemyData*> enemiesToKill;
    float randMove = 0.8;
    int wiggleX, wiggleY;
    for (EnemyData* enemy : *objectsHandler->getEnemyHolder()) {
        sf::Vector2f preDirVec = enemy->getPos() - playerData.getPos();
        float length = std::sqrt(preDirVec.x * preDirVec.x + preDirVec.y * preDirVec.y);
        preDirVec += sf::Vector2f({ (rand() % 12) * preDirVec.x / 12, (rand() % 12) * preDirVec.y / 12 });
        length = std::sqrt(preDirVec.x * preDirVec.x + preDirVec.y * preDirVec.y);
        if (fabs(length) >= 0.5) {
            preDirVec /= length;
            enemy->move(-1.f *preDirVec);
        }
        sf::Vector2f postDirVec = enemy->getPos() - playerData.getPos();
        wiggleX = (postDirVec.x + 216)/27;
        wiggleY = (postDirVec.y + 135)/ 18;
        if (wiggleX >= 0 && wiggleX < 16 && wiggleY >= 0 && wiggleY < 15) {
            if (enemyWiggleHelper[wiggleX][wiggleY]) {
                if (fabs(preDirVec.x) > fabs(preDirVec.y)) {
                    enemy->move({ (float) (rand() / RAND_MAX - 0.5)*0.5f, (float)(rand() / RAND_MAX - 0.5) * 0.2f });
                    if (postDirVec.y > 0 && wiggleY + 1 < 15)
                        enemy->move({ 0, randMove });
                    else if (wiggleY - 1 >= 0)
                        enemy->move({ 0, -randMove });
                } else {
                    enemy->move({ (float)(rand() / RAND_MAX - 0.5) * 0.2f, (float)(rand() / RAND_MAX - 0.5)*0.5f });
                    if (postDirVec.x > 0 && wiggleX + 1 < 16)
                        enemy->move({ randMove, 0 });
                    else if (wiggleX - 1 >= 0)
                        enemy->move({ -randMove, 0 });   
                }
                if (rand() % 2 == 0)
                    enemyWiggleHelper[wiggleX][wiggleY] = false;
            }
            else
                enemyWiggleHelper[wiggleX][wiggleY] = true;
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
    memset(enemyWiggleHelper, false, 16 * 15 * sizeof(bool));
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
        for (int i = 0; i < 20; i++) 
            objectsHandler->addEnemy(static_cast<int>(timer.getElapsedTime().asSeconds() / 60), randomizePos(), (seconds % 30 == 0 && i == 0) ? true : false);
    }
}

void PlaySpace::setHud() {
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setTextureRect({ {0, 8} , { (int)(((float)playerData.getXp() / playerData.getXpToNext()) * 394), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setTextureRect({ {0, 16} , { (int)(((float)playerData.getCurrentHp() / playerData.getEffectiveMaxHp()) * 200), 8} });
    objectsHandler->getSpritePointer(hudHolderIndex, 0)->setPosition({ 36 + std::round(playerData.getPos().x) - 208, 1 + std::round(playerData.getPos().y) - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 1)->setPosition({ 36 + std::round(playerData.getPos().x) - 208, 1 + std::round(playerData.getPos().y) - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 2)->setPosition({ 36 + std::round(playerData.getPos().x) - 208, 10 + std::round(playerData.getPos().y) - 123 });
    objectsHandler->getSpritePointer(hudHolderIndex, 3)->setPosition({ 36 + std::round(playerData.getPos().x) - 208, 10 + std::round(playerData.getPos().y) - 123 });
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
    objectsHandler->loadTextIntoHolder("LVL:1", 14, { SCENEWIDTH/32 - objectsHandler->calculateTextWidth("LVL:1",14)/2 , 0 });
    sf::Texture* hudTexture = objectsHandler->loadTexture({ 394, 24 }, "HudElements");
    hudHolderIndex = objectsHandler->addVectorToSpriteHolder();
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 394,8 }, { 0, 0 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 36, 1 });
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 394,8 }, { 0, 8 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 36, 1 });
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 200,8 }, { 0, 0 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 36, 10 });
    objectsHandler->loadSpriteIntoHolder(*hudTexture, { 200,8 }, { 0, 16 }, hudHolderIndex);
    objectsHandler->getSpritePointer(hudHolderIndex, -1)->setPosition({ 36, 10 });
    sf::Texture* enemyTexture = objectsHandler->loadTexture({ 80, 48 }, "EnemySprites");
    sf::Texture* projectileTexture = objectsHandler->loadTexture({ 12, 12 }, "ProjectileSprites");
    sf::Texture* powerUpTexture = objectsHandler->loadTexture({ 40, 10 }, "PowerUps");
    if (!enemyTexture)
        return true;
    if (!projectileTexture)
        return true;
    if (!powerUpTexture)
        return true;
    return false; 
}

void PlaySpace::cleanUp() {
    playerData.cleanUp();
    objectsHandler->clearSpriteHolder();
    objectsHandler->clearTextHolder();
    objectsHandler->clearEnemyHolder();
    objectsHandler->clearProjectileHolder();
    objectsHandler->clearPowerUpHolder();
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
    return static_cast<int>(timer.getElapsedTime().asSeconds())/5 + additionalCoins;
}

bool PlaySpace::getShouldRun() {
    return paused || levelingUp;
}