#pragma once
#include "Scene.h"

/**
 * @class ResetChoice
 * Klasa reprezentuj¹ca scenê potwierdzenia resetu
 */
class ResetChoice : public Scene {
private:
	/**
	* @brief Indeks aktualnie wybranego przycisku.
	*/
	int selectedButton;
	/**
	* @brief Indeks w `ObjectsHandler` do kolekcji sprite'ów u¿ywanej przez tê scenê.
	*/
	int spriteHolderIndex;
	/**
	* @brief WskaŸnik u¿ywany do modyfikacji ustawieñ wyœwietlania.
	*/
	Display* display;
	/**
	 * @brief Odœwie¿a wizualne wskazanie aktualnie wybranego przycisku.
	 */
	void refreshSelection();
public:
	using Scene::Scene;
	/**
	 * @brief Ustawia wskaŸnik do obiektu `Display`.
	 * @param readDisplay WskaŸnik na obiekt klasy `Display`.
	 */
	void setDisplay(Display* readDisplay);
	/**
	 * @brief Przetwarza logikê zdarzeñ specyficzn¹ dla sceny potwierdzenia resetu.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan pocz¹tkowy sceny potwierdzenia resetu.
	 * @return `false`, jeœli inicjalizacja zakoñczy³a siê pomyœlnie, `true` w przypadku b³êdu.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê potwierdzenia resetu przed jej zniszczeniem.
	 */
	void cleanUp();
};