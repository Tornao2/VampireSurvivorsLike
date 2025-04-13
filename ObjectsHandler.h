#pragma once
#include <SFML/Graphics.hpp>
#include <FastNoiseLite.h>
#include "EnemyData.h"
#include "Projectiles.h"

#define CHUNKSIZE 16
#define TILESIZE 16

struct Tile {
	sf::Sprite* sprite = nullptr;
	int type = 0;
};

struct Chunk {
	Tile tiles[CHUNKSIZE][CHUNKSIZE];
	bool generate = false;
};

struct PairHash {
	size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

class ObjectsHandler {
	std::unordered_map<std::string, sf::Texture> textureHolder;
	sf::Font font;
	std::vector <sf::Text> textHolder;
	std::list <EnemyData*> enemyHolder;
	std::vector <std::vector<sf::Sprite>*> spriteHolder;
	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> chunkMap;
	std::list <Projectiles*> projectileHolder;
public:
	sf::Texture* loadTexture(sf::Vector2i size, std::string fileName);
	void loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, int index);
	int addVectorToSpriteHolder();
	void clearSpriteHolder();
	std::vector <std::vector<sf::Sprite>*>* getSpriteHolder();
	sf::Sprite* getSpritePointer(int collectionIndex, int spriteIndex);
	int getSpriteHolderSize(int collectionIndex);
	bool loadFont();
	std::vector <sf::Text>* getTextHolder();
	sf::Text* getTextPointer(int textIndex);
	void clearTextHolder();
	void loadTextIntoHolder(std::string readText, unsigned char size, sf::Vector2f position);
	float calculateTextWidth(std::string readText, unsigned char size);
	void generateChunk(int chunkX, int chunkY);
	void deleteUnusedChunks();
	void falseAllChunks();
	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> getChunkMap();
	void addEnemy(int enemyId, sf::Vector2f readPos, bool readIsBoss);
	void clearEnemyHolder();
	std::list <EnemyData*>* getEnemyHolder();
	void killEnemy(std::list<EnemyData*> enemiesToKill);
	sf::Vector2f getClosestEnemyCords(sf::Vector2f readPlayerPos);
	void addProjectile(float damageMod, int projectileId, sf::Vector2f readPos, sf::Vector2f readEndPos);
	void clearProjectileHolder();
	std::list <Projectiles*>* getProjectileHolder();
	void destroyProjectiles(std::list<Projectiles*> projectilesToDestroy);
	void cleanChunkHolder();
};