#pragma once
#include "Scene.h"
#include "Modifiers.h"
#include "Unlocks.h"

/**
 * @class FinishScreen
 * Klasa reprezentuj¹ca scenê wyœwietlan¹ po zakoñczeniu rozgrywki.
 */
class FinishScreen : public Scene {
private:
	/**
	* Indeks kolekcji sprite'ów u¿ywanej przez tê scenê w ObjectsHandler.
	*/
	int spriteHolderIndex;
	/**
	 * @brief Pusta funkcja.
	 */
	void refreshSelection();
	/**
	* Liczba monet zdobytych podczas ostatniej rozgrywki.
	*/
	int coins = 0;
	/**
	* Flaga wskazuj¹ca, czy w wyniku ostatniej rozgrywki coœ zosta³o odblokowane.
	*/
	bool unlocked = false;

public:
	using Scene::Scene;
	/**
	 * @brief Ustawia liczbê zdobytych monet i obs³uguje logikê odblokowania mapy/postaci.
	 * @param readCoins Liczba zdobytych monet.
	 * @param chosenMap Indeks mapy, na której zakoñczono rozgrywkê.
	 * @param chosenChar Indeks postaci, któr¹ grano.
	 */
	void setCoins(int readCoins, int chosenMap, int chosenChar);
	/**
	 * @brief Obs³uguje logikê zdarzeñ specyficzn¹ dla ekranu zakoñczenia.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return Wartoœæ logiczna wskazuj¹ca czy nale¿y kontynuowaæ dzia³anie sceny.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan sceny ekranu zakoñczenia.
	 * @return Wartoœæ logiczna wskazuj¹ca, czy inicjalizacja przebieg³a pomyœlnie.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê ekranu zakoñczenia przed jej zniszczeniem.
	 */
	void cleanUp();
};