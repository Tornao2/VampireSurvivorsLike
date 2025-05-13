#pragma once
#include "Scene.h"
#include "CharacterData.h" 

/**
 * @class PlayChoice
 * Klasa reprezentuj¹ca scenê wyboru postaci i mapy przed rozpoczêciem gry.
 */
class PlayChoice : public Scene {
private:
	/**
	* @brief WskaŸnik do zmiennej przechowuj¹cej indeks wybranej mapy.
	*/
	int* selectedMap;
	/**
	* @brief WskaŸnik do zmiennej przechowuj¹cej indeks wybranej postaci gracza.
	*/
	int* selectedPlayer;
	/**
	* @brief Indeks aktualnie wybranego rzêdu w interfejsie wyboru (np. postaæ lub mapa).
	*/
	int selectedRow;
	/**
	* @brief Indeks kolekcji sprite'ów u¿ywanej przez tê scenê.
	*/
	int spriteHolderIndex;
	/**
	* @brief Wektor flag wskazuj¹cych, które postacie s¹ odblokowane i dostêpne do wyboru.
	*/
	std::vector<bool> unlockedChars;
	/**
	* @brief Wektor flag wskazuj¹cych, które mapy s¹ odblokowane i dostêpne do wyboru.
	*/
	std::vector<bool> unlockedMaps;
	/**
	 * @brief Odœwie¿a wizualne wskazanie aktualnie wybranego elementu oraz wskazanej mapy/postaci.
	 */
	void refreshSelection();
	/**
	 * @brief Odœwie¿a wyœwietlane statystyki dla aktualnie podœwietlonej postaci.
	 */
	void refreshCharacterStats();
public:
	using Scene::Scene; 
	/**
	 * @brief Przetwarza logikê zdarzeñ specyficzn¹ dla sceny wyboru postaci i mapy.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan pocz¹tkowy sceny wyboru postaci i mapy.
	 * @return `false`, jeœli inicjalizacja zakoñczy³a siê pomyœlnie, `true` w przypadku b³êdu.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê wyboru postaci i mapy przed jej zniszczeniem.
	 */
	void cleanUp();
	/**
	 * @brief Ustawia wskaŸniki do zmiennych, w których zostanie zapisany wybór mapy i postaci.
	 * @param readMap WskaŸnik do zmiennej ca³kowitoliczbowej, gdzie zostanie zapisany indeks wybranej mapy.
	 * @param readPlayer WskaŸnik do zmiennej ca³kowitoliczbowej, gdzie zostanie zapisany indeks wybranej postaci.
	 */
	void setPointers(int* readMap, int* readPlayer);
};