#pragma once
#include "Scene.h"
#include "Modifiers.h" 
/**
 * @class UpgradeScene
 * Klasa reprezentuj¹ca scenê ulepszeñ postaci lub ekwipunku.
 */
class UpgradeScene : public Scene {
private:
	/**
	* @brief Indeks kolekcji sprite'ów u¿ywanej przez tê scenê.
	*/
	int spriteHolderIndex;
	/**
	* @brief Indeks aktualnie wybranego rzêdu w menu ulepszeñ.
	*/
	int selectedRow;
	/**
	* @brief Indeks aktualnie wybranej kolumny w menu ulepszeñ.
	*/
	int selectedColumn;
	/**
	* @brief Ca³kowita liczba rzêdów dostêpnych opcji ulepszeñ.
	*/
	unsigned char upgrRowsAmount;
	/**
	* @brief WskaŸnik do tablicy przechowuj¹cej liczbê kolumn dla ka¿dego rzêdu ulepszeñ.
	*/
	unsigned char* colAmounts;
	/**
	* @brief Obiekt zajmuj¹cy siê zarz¹dzaniem ulepszeñ(³adowanie/zapisywanie etc).
	*/
	Modifiers modifiers;
	/**
	 * @brief Odœwie¿a wizualne wskazanie aktualnie wybranego elementu.
	 */
	void refreshSelection();
public:
	using Scene::Scene;
	/**
	 * @brief Wczytuje aktualne modyfikatory.
	 */
	void loadModifiers();
	/**
	 * @brief Przetwarza logikê zdarzeñ specyficzn¹ dla sceny ulepszeñ.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan pocz¹tkowy sceny ulepszeñ.
	 * @return `false`, jeœli inicjalizacja zakoñczy³a siê pomyœlnie, `true` w przypadku b³êdu.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê ulepszeñ przed jej zniszczeniem.
	 */
	void cleanUp();
};