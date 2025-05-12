#pragma once
#include <SFML/Graphics.hpp>
#include <FastNoiseLite.h>
/**
* Szerokoœæ i wysokoœæ chunku w kafelkach.
*/
#define CHUNKSIZE 16
/**
* Rozmiar boku pojedynczego kafelka w pikselach.
*/
#define TILESIZE 16
/**
 * @enum TerrainType
 * Wyliczenie okreœlaj¹ce typ terenu dla pojedynczego kafelka mapy.
 */
enum TerrainType {
	/**
	* Teren, po którym mo¿na chodziæ.
	*/
	walkable = 1,
	/**
	* Œciana.
	*/
	solid,
	/**
	* Teren œliski.
	*/
	slippery,
	/**
	* Teren zadaj¹cy obra¿enia.
	*/
	damaging
};
/**
 * @struct Tile
 * Struktura reprezentuj¹ca pojedynczy kafelek na mapie.
 */
struct Tile {
	/**
	* WskaŸnik do obiektu graficznego reprezentuj¹cego kafelek.
	*/
	sf::Sprite* sprite = nullptr;
	/**
	* Typ terenu tego kafelka.
	*/
	TerrainType type = walkable;
};
/**
 * @struct Chunk
 * Struktura reprezentuj¹ca fragment (chunk) mapy, sk³adaj¹cy siê z siatki kafelków.
 */
struct Chunk {
	/**
	* Dwuwymiarowa tablica kafelków tworz¹cych chunk.
	*/
	Tile tiles[CHUNKSIZE][CHUNKSIZE];
	/**
	* Flaga wskazuj¹ca, czy ten chunk jest aktualnie u¿ywany.
	*/
	bool generate = false;
};
/**
 * @struct PairHash
 * Funktor haszuj¹cy dla par liczb ca³kowitych, u¿ywany jako funkcja haszuj¹ca w mapie chunków.
 */
struct PairHash {
	/**
	 * @brief Operator wywo³ania funkcji, obliczaj¹cy hash dla pary.
	 * @param p Para liczb ca³kowitych do zahaszowania.
	 * @return Obliczona wartoœæ hashu.
	 */
	size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};
/**
 * @class MapGenerator
 * Klasa odpowiedzialna za proceduralne generowanie mapy gry,
 * zarz¹dzanie jej fragmentami oraz ich w³aœciwoœciami.
 */
class MapGenerator {
private:
	/**
	* Identyfikator aktualnie wybranej mapy do generowania.
	*/
	int mapId;
	/**
	* WskaŸnik do arkusza tekstur u¿ywanego do rysowania kafelków mapy.
	*/
	sf::Texture* textures;
	/**
	* Mapa przechowuj¹ca wygenerowane chunki, kluczem jest para wspó³rzêdnych chunka.
	*/
	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> chunkMap;
	/**
	 * @brief Wype³nia dany chunk kafelkami zgodnie z algorytmem dla mapy 1.
	 * @param chunk WskaŸnik do chunka, który ma zostaæ wype³niony.
	 * @param chunkX Wspó³rzêdna X chunka w siatce chunków.
	 * @param chunkY Wspó³rzêdna Y chunka w siatce chunków.
	 */
	void fillTilesMap1(Chunk* chunk, int chunkX, int chunkY);
	/**
	 * @brief Wype³nia dany chunk kafelkami zgodnie z algorytmem dla mapy 2.
	 * @param chunk WskaŸnik do chunka, który ma zostaæ wype³niony.
	 * @param chunkX Wspó³rzêdna X chunka w siatce chunków.
	 * @param chunkY Wspó³rzêdna Y chunka w siatce chunków.
	 */
	void fillTilesMap2(Chunk* chunk, int chunkX, int chunkY);
	/**
	 * @brief Wype³nia dany chunk kafelkami zgodnie z algorytmem dla mapy 3.
	 * @param chunk WskaŸnik do chunka, który ma zostaæ wype³niony.
	 * @param chunkX Wspó³rzêdna X chunka w siatce chunków.
	 * @param chunkY Wspó³rzêdna Y chunka w siatce chunków.
	 */
	void fillTilesMap3(Chunk* chunk, int chunkX, int chunkY);
public:
	/**
	 * @brief Ustawia identyfikator mapy, która ma byæ generowana.
	 * @param readId Identyfikator mapy.
	 */
	void setMapId(int readId);
	/**
	 * @brief Generuje chunk o podanych wspó³rzêdnych w siatce chunków.
	 * @param chunkX Wspó³rzêdna X chunka w siatce chunków.
	 * @param chunkY Wspó³rzêdna Y chunka w siatce chunków.
	 */
	void generateChunk(int chunkX, int chunkY);
	/**
	 * @brief Usuwa z pamiêci chunki, które nie s¹ oznaczone flag¹ generated.
	 */
	void deleteUnusedChunks();
	/**
	 * @brief Ustawia flagê 'generate' na fa³sz dla wszystkich chunków.
	 */
	void falseAllChunks();
	/**
	 * @brief Zwraca mapê przechowuj¹c¹ wszystkie aktywne chunki.
	 * @return Mapa chunków.
	 */
	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> getChunkMap();
	/**
	 * @brief Czyœci ca³kowicie mapê chunków, usuwaj¹c wszystkie chunki z pamiêci.
	 */
	void cleanChunkHolder();
	/**
	 * @brief Ustawia wskaŸnik do arkusza tekstur, który ma byæ u¿ywany przez generator.
	 * @param readText WskaŸnik do arkusza tekstur.
	 */
	void setTextures(sf::Texture* readText);
};