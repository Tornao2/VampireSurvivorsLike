#pragma once
#include <SFML/Graphics.hpp>

using ListOrVector = std::variant<std::vector<sf::Sprite>*, std::list<sf::Sprite>*>;

class SpriteHandler {
	std::unordered_map<std::string, sf::Texture> textureHolder;
	std::vector <ListOrVector>* spriteHolder = new std::vector<ListOrVector>;
public:
	sf::Texture* loadTexture(sf::Vector2i size, std::string fileName);
	void loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, int index);
	int addVectorToSpriteHolder();
	int addListToSpriteHolder();
	void clearSpriteHolder();
	void destroyTextures();
	std::vector <ListOrVector>** getSpriteHolder();
	sf::Sprite* getSpritePointer(int collectionIndex, int spriteIndex);
};