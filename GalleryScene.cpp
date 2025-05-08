#include "GalleryScene.h"

void GalleryScene::refreshSelection() {
	for (sf::Text& text : *objectsHandler->getTextHolder())
		text.setFillColor(sf::Color::White);
	objectsHandler->getTextPointer(selectedRow)->setFillColor(GREEN);
}
	
bool GalleryScene::eventLogic(std::optional<sf::Event> gameEvent) {
	if (gameEvent->is<sf::Event::Closed>())
		return true;
    else if (gameEvent->is<sf::Event::KeyPressed>()) {
        if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
			selectedRow++;
            soundManager->playSound("menuChange", true);
            if (selectedRow == 6)
				selectedRow = 0;
			showSprites();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
			selectedRow--;
            soundManager->playSound("menuChange", true);
            if (selectedRow == -1)
				selectedRow = 5;
			showSprites();
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            soundManager->playSound("menuSelect", true);
			if (selectedRow == 5) {
				*sceneLabel = MAINMENU;
				return true;
			}
        }
        refreshSelection();
    }
    return false;
}
	
void GalleryScene::showSprites() {
	objectsHandler->getSpriteHolder()->at(additionalHolderIndex)->clear();
	sf::Texture* usedTexture;
	switch (selectedRow) {
		case 0:
			usedTexture = objectsHandler->loadTexture({ 64, 24 }, "CharacterSprites");
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 16,24 }, { 0, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 201, 87 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 16,24 }, { 16, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 312, 87 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 16,24 }, { 32, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 201, 160 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 16,24 }, { 48, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 312, 160 });
			break;
		case 1:
			usedTexture = objectsHandler->loadTexture({ 80, 48 }, "EnemySprites");
			for (int i = 0; i < 8; i++) {
				objectsHandler->loadSpriteIntoHolder(*usedTexture, { 16,24 }, { (i % 4) * 16, i / 4 * 24 }, additionalHolderIndex);
				objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 142 + 66.f * (i%4), 89 + i/4 * 73.f });
			}
			break;
		case 2:
			usedTexture = objectsHandler->loadTexture({ 96, 62 }, "ItemSprites");
			for (int i = 0; i < 5; i++) {
				objectsHandler->loadSpriteIntoHolder(*usedTexture, { 32,31 }, { (i % 3) * 32, i / 3 * 31 }, additionalHolderIndex);
				objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 129 + i * 55.f, 61 });
			}
			usedTexture = objectsHandler->loadTexture({ 160, 62 }, "WeaponSprites");
			for (int i = 0; i < 10; i++) {
				objectsHandler->loadSpriteIntoHolder(*usedTexture, { 32,31 }, { (i % 5) * 32, i / 5 * 31 }, additionalHolderIndex);
				objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 129 + (i%5) * 55.f, 100 + i /5 * 42.f });
			}
			usedTexture = objectsHandler->loadTexture({ 51, 21 }, "ProjectileSprites");
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 9,9 }, { 0,0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 141, 133 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 9,9 }, { 9,0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 197, 133 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 12,7 }, { 27, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 251, 133 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 12,7 }, { 12, 9 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 304, 133 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 10,5 }, { 36, 9 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 359, 133 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 9,9 }, { 18, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 141, 179 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 12,7 }, { 39, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 196, 179 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 12,7 }, { 0, 9 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 251, 179 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 12,7 }, { 24, 9 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 304, 179 });
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 10,5 }, { 0, 16 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 359, 179 });
			break;
		case 3:
			usedTexture = objectsHandler->loadTexture({ 32, 32 }, "TexturesMap1");
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 32,32 }, { 0, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 191, 95 });
			usedTexture = objectsHandler->loadTexture({ 32, 32 }, "TexturesMap2");
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 32,32 }, { 0, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 304, 95 });
			usedTexture = objectsHandler->loadTexture({ 32, 16 }, "TexturesMap3");
			objectsHandler->loadSpriteIntoHolder(*usedTexture, { 32,16 }, { 0, 0 }, additionalHolderIndex);
			objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 245, 168 });
			break;
		case 4:
			usedTexture = objectsHandler->loadTexture({ 50, 10 }, "PowerUps");
			for (int i = 0; i < 5; i++) {
				objectsHandler->loadSpriteIntoHolder(*usedTexture, { 10,10 }, { (i % 5) * 10, 0 }, additionalHolderIndex);
				objectsHandler->getSpritePointer(additionalHolderIndex, -1)->setPosition({ 140 + i * 55.f, 130 });
			}
			break;
	}
}

bool GalleryScene::init() {
	selectedRow = 0;
	sf::Texture* backgroundTexture = objectsHandler->loadTexture({ 432, 270 }, "SettingsBG");
	if (!backgroundTexture)
		return true;
	spriteHolderIndex = objectsHandler->addVectorToSpriteHolder();
	objectsHandler->loadSpriteIntoHolder(*backgroundTexture, { 432,270 }, { 0, 0 }, spriteHolderIndex);
	sf::Texture* buttonTexture = objectsHandler->loadTexture({ 434, 102 }, "ButtonSprites");
	if (!buttonTexture)
		return true;
	for (int i = 0; i < 6; i++) {
		objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
		objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 0, 45.f * i +1});
	}
	sf::Texture* menuTexture = objectsHandler->loadTexture({ 332, 220 }, "PauseBackground");
	if (!menuTexture)
		return true;
	objectsHandler->loadSpriteIntoHolder(*menuTexture, { 332,220 }, { 0, 0 }, spriteHolderIndex);
	objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 95, 25 });
	objectsHandler->loadTextIntoHolder("Characters", 21, { 45 - (objectsHandler->calculateTextWidth("Characters", 21)) / 2, 6 });
	objectsHandler->loadTextIntoHolder("Enemies", 21, { 45 - (objectsHandler->calculateTextWidth("Enemies", 21)) / 2, 51 });
	objectsHandler->loadTextIntoHolder("Items", 21, { 45 - (objectsHandler->calculateTextWidth("Items", 21)) / 2, 96 });
	objectsHandler->loadTextIntoHolder("Map tiles", 21, { 45 - (objectsHandler->calculateTextWidth("Map tiles", 21)) / 2, 141 });
	objectsHandler->loadTextIntoHolder("PowerUps", 21, { 45 - (objectsHandler->calculateTextWidth("PowerUps", 21)) / 2, 186 });
	objectsHandler->loadTextIntoHolder("Exit", 21, { 45 - (objectsHandler->calculateTextWidth("Exit", 21)) / 2, 231 });
	refreshSelection();
	additionalHolderIndex = objectsHandler->addVectorToSpriteHolder();
	showSprites();
	return false;
}
	
void GalleryScene::cleanUp() {
	objectsHandler->clearSpriteHolder();
	objectsHandler->clearTextHolder();
}