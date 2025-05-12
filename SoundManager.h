#pragma once
#include <SFML/Audio.hpp>

/**
 * @class SoundManager
 * Klasa odpowiedzialna za ³adowanie, przechowywanie, odtwarzanie
 * i zarz¹dzanie g³oœnoœci¹ efektów dŸwiêkowych w aplikacji.
 */
class SoundManager {
	/**
	* Kontener przechowuj¹cy za³adowane bufory dŸwiêkowe.
	*/
	std::vector<sf::SoundBuffer> soundBuffers;
	/**
	* Mapa przechowuj¹ca wskaŸniki do odtwarzalnych dŸwiêków.
	*/
	std::unordered_map<std::string, sf::Sound*> soundHolders;
public:
	/**
	 * @brief £aduje wszystkie niezbêdne pliki dŸwiêkowe do pamiêci.
	 */
	void loadSounds();
	/**
	 * @brief Odtwarza dŸwiêk o podanym identyfikatorze tekstowym.
	 * @param text Identyfikator tekstowy dŸwiêku do odtworzenia.
	 * @param checkBreak Flaga wskazuj¹ca, czy przerwaæ odtwarzanie poprzedniego dŸwiêku o tym samym identyfikatorze, jeœli nie minê³o 50ms.
	 */
	void playSound(std::string text, bool checkBreak);
	/**
	 * @brief Ustawia poziom g³oœnoœci dla wszystkich zarz¹dzanych dŸwiêków.
	 * @param volume Nowy poziom g³oœnoœci.
	 */
	void setSoundVolume(int volume);
};