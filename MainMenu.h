#pragma once
#include "Scene.h"

/**
 * @class MainMenu
 * Klasa reprezentuj¹ca scenê menu g³ównego.
 */
class MainMenu : public Scene {
private:
	/**
	* @brief Indeks kolekcji sprite'ów u¿ywanej przez tê scenê.
	*/
	int spriteHolderIndex;
	/**
	* @brief Indeks aktualnie wybranego przycisku w menu.
	*/
	int selectedButton;
	/**
	 * @brief Odœwie¿a wizualne wskazanie aktualnie wybranego przycisku.
	 */
	void refreshSelection();
public:
	using Scene::Scene; 
	/**
	 * @brief Przetwarza logikê zdarzeñ specyficzn¹ dla sceny menu g³ównego.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan pocz¹tkowy sceny menu g³ównego.
	 * @return `false`, jeœli inicjalizacja zakoñczy³a siê pomyœlnie, `true` w przypadku b³êdu.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê menu g³ównego przed jej zniszczeniem.
	 */
	void cleanUp();
};