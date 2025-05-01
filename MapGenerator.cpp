#include "MapGenerator.h"

void MapGenerator::setMapId(int readId) {
    mapId = readId;
}

void MapGenerator::setTextures(sf::Texture* readText) {
    textures = readText;
}

void MapGenerator::fillTilesMap1(Chunk* chunk, int chunkX, int chunkY) {
    FastNoiseLite noise(FastNoiseLite::DomainWarpType_OpenSimplex2);
    noise.SetFrequency(0.005);
    for (int i = 0; i < CHUNKSIZE; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) {
            float value = noise.GetNoise((float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE);
            int terrain;
            if (value < -0.75)
                terrain = 0;
            else if (value < 0.35 || (0.45 <= value && value < 0.9))
                terrain = 1;
            else if (0.35 <= value && value < 0.45)
                terrain = 2;
            else
                terrain = 3;
            switch (terrain) {
            case 0:
                chunk->tiles[i][j].type = solid;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({0, 0 }, { 16, 16 }));
                break;
            case 1:
            case 2:
            case 3:
                chunk->tiles[i][j].type = walkable;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({ 16 * (terrain % 2), terrain > 1 ? 16 : 0 }, { 16, 16 }));
                break;
            }
            chunk->tiles[i][j].sprite->setPosition({ (float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE });
        }
    }
}

void MapGenerator::fillTilesMap2(Chunk* chunk, int chunkX, int chunkY) {
    FastNoiseLite noise(FastNoiseLite::DomainWarpType_OpenSimplex2);
    noise.SetFrequency(0.007);
    noise.SetSeed(1111);
    for (int i = 0; i < CHUNKSIZE; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) {
            float value = noise.GetNoise((float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE);
            int terrain;
            if (value < -0.05)
                terrain = 0;
            else if (value < 0.35 || (0.45 <= value && value < 0.9))
                terrain = 1;
            else if (0.35 <= value && value < 0.45)
                terrain = 2;
            else
                terrain = 3;
            switch (terrain) {
            case 0:
                chunk->tiles[i][j].type = walkable;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({ 0, 0 }, { 16, 16 }));
                break;
            case 1:
                chunk->tiles[i][j].type = slippery;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({ 16, 0 }, { 16, 16 }));
                break;
            case 2:
            case 3:
                chunk->tiles[i][j].type = solid;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({ 16 * (terrain % 2), 16 }, { 16, 16 }));
                break;
            }
            chunk->tiles[i][j].sprite->setPosition({ (float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE });
        }
    }
}

void MapGenerator::fillTilesMap3(Chunk* chunk, int chunkX, int chunkY) {
    FastNoiseLite noise(FastNoiseLite::CellularReturnType_Distance2Add);
    noise.SetFrequency(0.003);
    noise.SetSeed(1232);
    for (int i = 0; i < CHUNKSIZE; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) {
            float value = noise.GetNoise((float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE);
            int terrain;
            if (value < 0)
                terrain = 0;
            else 
                terrain = 1;
            switch (terrain) {
            case 0:
                chunk->tiles[i][j].type = walkable;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({ 16, 0 }, { 16, 16 }));
                break;
            case 1:
                chunk->tiles[i][j].type = damaging;
                chunk->tiles[i][j].sprite = new sf::Sprite(*textures, sf::IntRect({ 0, 0 }, { 16, 16 }));
                break;
            }
            chunk->tiles[i][j].sprite->setPosition({ (float)chunkX * TILESIZE * CHUNKSIZE + i * TILESIZE, (float)chunkY * TILESIZE * CHUNKSIZE + j * TILESIZE });
        }
    }
}

std::unordered_map<std::pair<int, int>, Chunk*, PairHash> MapGenerator::getChunkMap() {
    return chunkMap;
}

void MapGenerator::generateChunk(int chunkX, int chunkY) {
    std::pair pair{ chunkX, chunkY };
    if (chunkMap.find(pair) != chunkMap.end()) {
        chunkMap.find(pair)->second->generate = true;
        return;
    }
    Chunk* chunk = new Chunk;
    chunk->generate = true;
    chunkMap[pair] = chunk;
    switch (mapId) {
    case 0:
        fillTilesMap1(chunk, chunkX, chunkY);
        break;
    case 1:
        fillTilesMap2(chunk, chunkX, chunkY);
        break;
    case 2:
        fillTilesMap3(chunk, chunkX, chunkY);
        break;
    }
}

void MapGenerator::cleanChunkHolder() {
    for (auto it = chunkMap.begin(); it != chunkMap.end(); ) {
        auto& value = it->second;
        for (int y = 0; y < CHUNKSIZE; ++y) {
            for (int x = 0; x < CHUNKSIZE; ++x) {
                Tile& tile = value->tiles[y][x];
                delete tile.sprite;
                tile.sprite = nullptr;
            }
        }
        delete value;
        it = chunkMap.erase(it);
    }
}

void MapGenerator::falseAllChunks() {
    for (auto& [key, value] : chunkMap)
        value->generate = false;
}

void MapGenerator::deleteUnusedChunks() {
    for (auto it = chunkMap.begin(); it != chunkMap.end(); ) {
        auto& value = it->second;
        if (!value->generate) {
            for (int y = 0; y < CHUNKSIZE; ++y) {
                for (int x = 0; x < CHUNKSIZE; ++x) {
                    Tile& tile = value->tiles[y][x];
                    delete tile.sprite;
                    tile.sprite = nullptr;
                }
            }
            delete value;
            it = chunkMap.erase(it);
        }
        else
            ++it;
    }
}