#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

/**
* Liczba dostêpnych map w grze.
*/
#define NUMBEROFMAPS 3
/**
* Liczba dostêpnych postaci w grze.
*/
#define NUMBEROFCHARS 4
/**
 * @class Unlocks
 * Klasa narzêdziowa odpowiedzialna za zapisywanie i wczytywanie
 * stanu odblokowanych elementów gry z plików.
 */
class Unlocks {
public:
	/**
	 * @brief Zapisuje stan odblokowania elementów do podanego pliku.
	 * @param boolArray Kontener przechowuj¹cy informacje o odblokowaniu poszczególnych elementów.
	 * @param filename Nazwa pliku, do którego ma zostaæ zapisany stan.
	 */
	void saveUnlocked(std::vector<bool> boolArray, std::string filename);
	/**
	 * @brief Wczytuje stan odblokowania elementów z podanego pliku.
	 * @param filename Nazwa pliku, z którego ma zostaæ wczytany stan.
	 * @return Kontener przechowuj¹cy wczytane informacje o odblokowaniu poszczególnych elementów.
	 */
	std::vector<bool> loadUnlocked(std::string filename);
};