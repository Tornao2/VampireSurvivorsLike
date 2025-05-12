#pragma once
#include "Scene.h"

/**
 * @class GalleryScene
 * Klasa reprezentuj¹ca scenê galerii.
 */
class GalleryScene : public Scene {
private: 
	/**
	* G³ówny indeks kolekcji sprite'ów u¿ywanej przez tê scenê w ObjectsHandler.
	*/
	int spriteHolderIndex;
	/**
	* Dodatkowy indeks kolekcji sprite'ów u¿ywanej przez tê scenê do podgl¹du wybranych sprite'ów.
	*/
	int additionalHolderIndex;
	/**
	* Indeks aktualnie wybranego rzêdu w galerii.
	*/
	int selectedRow;
	/**
	 * @brief Odœwie¿a wizualne wskazanie aktualnie wybranego elementu w galerii.
	 */
	void refreshSelection();
	/**
	 * @brief Wyœwietla odpowiednie sprite'y dla aktualnie wybranego elementu galerii.
	 */
	void showSprites();
public:
	using Scene::Scene;
	/**
	 * @brief Obs³uguje logikê zdarzeñ specyficzn¹ dla sceny galerii.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return Wartoœæ logiczna wskazuj¹ca czy nale¿y kontynuowaæ dzia³anie sceny.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan sceny galerii.
	 * @return Wartoœæ logiczna wskazuj¹ca, czy inicjalizacja przebieg³a pomyœlnie.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê galerii przed jej zniszczeniem.
	 */
	void cleanUp();
};