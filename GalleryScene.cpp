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
            if (selectedRow == 7)
				selectedRow = 0;
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
			selectedRow--;
            soundManager->playSound("menuChange", true);
            if (selectedRow == -1)
				selectedRow = 6;
        }
        else if (gameEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
            soundManager->playSound("menuSelect", true);
			if (selectedRow == 6) {
				*sceneLabel = MAINMENU;
				return true;
			}
        }
        refreshSelection();
    }
    return false;
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
	for (int i = 0; i < 7; i++) {
		objectsHandler->loadSpriteIntoHolder(*buttonTexture, { 90,38 }, { 270, 38 }, spriteHolderIndex);
		objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 0, 38.f * i +1});
	}
	sf::Texture* menuTexture = objectsHandler->loadTexture({ 332, 220 }, "PauseBackground");
	if (!menuTexture)
		return true;
	objectsHandler->loadSpriteIntoHolder(*menuTexture, { 332,220 }, { 0, 0 }, spriteHolderIndex);
	objectsHandler->getSpritePointer(spriteHolderIndex, -1)->setPosition({ 95, 25 });
	objectsHandler->loadTextIntoHolder("Characters", 21, { 45 - (objectsHandler->calculateTextWidth("Characters", 21)) / 2, 6 });
	objectsHandler->loadTextIntoHolder("Enemies", 21, { 45 - (objectsHandler->calculateTextWidth("Enemies", 21)) / 2, 44 });
	objectsHandler->loadTextIntoHolder("Items", 21, { 45 - (objectsHandler->calculateTextWidth("Items", 21)) / 2, 82 });
	objectsHandler->loadTextIntoHolder("Projectiles", 21, { 45 - (objectsHandler->calculateTextWidth("Projectiles", 21)) / 2, 120 });
	objectsHandler->loadTextIntoHolder("Map tiles", 21, { 45 - (objectsHandler->calculateTextWidth("Map tiles", 21)) / 2, 158 });
	objectsHandler->loadTextIntoHolder("PowerUps", 21, { 45 - (objectsHandler->calculateTextWidth("PowerUps", 21)) / 2, 196 });
	objectsHandler->loadTextIntoHolder("Exit", 21, { 45 - (objectsHandler->calculateTextWidth("Exit", 21)) / 2, 234 });
	refreshSelection();
	return false;
}
	
void GalleryScene::cleanUp() {
	objectsHandler->clearSpriteHolder();
	objectsHandler->clearTextHolder();
}