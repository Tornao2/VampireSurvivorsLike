#pragma once
#include <SFML/Graphics.hpp>

class SpriteHandler {
	std::unordered_map<std::string, sf::Texture> textureHolder;
	std::vector < std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*>> spriteHolder;
public:
	sf::Texture* loadTexture(sf::Vector2i size, std::string fileName);
	void loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*> collection);
	std::vector<sf::Sprite>* addVectorToSpriteHolder();
	std::list<sf::Sprite>* addListToSpriteHolder();
	void removeCollectionFromSpriteHolder(std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*>* readCollection);
	void clearSpriteHolder();
	void destroyTextures();
	std::vector < std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*>>& getSpriteHolder();
};