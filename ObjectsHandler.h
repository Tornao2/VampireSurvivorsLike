#pragma once
#include "MapGenerator.h"
#include "EnemyData.h"
#include "Projectiles.h"

class ObjectsHandler {
	sf::Font font;
	std::vector <sf::Text> textHolder;
	std::list <EnemyData*> enemyHolder;
	std::vector <std::vector<sf::Sprite>*> spriteHolder;
	std::list <Projectiles*> projectileHolder;
	std::unordered_map<std::string, sf::Texture> textureHolder;
	MapGenerator generator;
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
	void addEnemy(int enemyId, sf::Vector2f readPos, bool readIsBoss);
	void clearEnemyHolder();
	std::list <EnemyData*>* getEnemyHolder();
	void killEnemy(std::list<EnemyData*> enemiesToKill);
	sf::Vector2f getClosestEnemyCords(sf::Vector2f readPlayerPos);
	void addProjectile(float damageMod, int projectileId, sf::Vector2f readPos, sf::Vector2f readEndPos);
	void clearProjectileHolder();
	std::list <Projectiles*>* getProjectileHolder();
	void destroyProjectiles(std::list<Projectiles*> projectilesToDestroy);
	MapGenerator* getMapGenerator();
	void setMap(int readMapId);
};