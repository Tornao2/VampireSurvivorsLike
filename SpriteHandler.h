#pragma once
#include <SFML/Graphics.hpp>

class SpriteHandler {
	std::unordered_map<std::string, sf::Texture> textureHolder;
public:
	sf::Texture* loadTexture(sf::Vector2i size, std::string fileName);
	sf::Sprite loadSprite(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position);
	void destroyTextures();
};