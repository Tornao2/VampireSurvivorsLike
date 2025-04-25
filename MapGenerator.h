#pragma once
#include <SFML/Graphics.hpp>
#include <FastNoiseLite.h>

#define CHUNKSIZE 16
#define TILESIZE 16

enum TerrainType {
	walkable = 1,
	solid
};

struct Tile {
	sf::Sprite* sprite = nullptr;
	TerrainType type = walkable;
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

class MapGenerator {
	int mapId;
	sf::Texture* textures;
	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> chunkMap;
public:
	void setMapId(int readId);
	void generateChunk(int chunkX, int chunkY);
	void fillTilesMap1(Chunk* chunk, int chunkX, int chunkY);
	void fillTilesMap2(Chunk* chunk, int chunkX, int chunkY);
	void fillTilesMap3(Chunk* chunk, int chunkX, int chunkY);
	void deleteUnusedChunks();
	void falseAllChunks();
	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> getChunkMap();
	void cleanChunkHolder();
	void setTextures(sf::Texture* readText);
};