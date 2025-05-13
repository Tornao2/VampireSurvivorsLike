#pragma once
#include "Scene.h" 

/**
 * @class SettingsScene
 * brief Klasa reprezentuj¹ca scenê ustawieñ gry.
 */
class SettingsScene : public Scene {
private:
	/**
	* @brief Indeks do kolekcji sprite'ów u¿ywanej przez tê scenê.
	*/
	int spriteHolderIndex;
	/**
	* @brief Indeks aktualnie wybranego rzêdu w menu ustawieñ.
	*/
	int selectedRow;
	/**
	* @brief Indeks aktualnie wybranej kolumny w menu ustawieñ.
	*/
	int selectedColumn;
	/**
	* @brief WskaŸnik do obiektu u¿ywany do aktualizacji ustawieñ wyœwietlania.
	*/
	Display* display;
	/**
	* @brief WskaŸnik do obiektu muzyki, której g³oœnoœæ mo¿e byæ dynamicznie kontrolowana w tej scenie.
	*/
	sf::Music* playedMusic;
	/**
	 * @brief Odœwie¿a wizualne wskazanie aktualnie wybranego elementu.
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
	 * @brief Przetwarza logikê zdarzeñ specyficzn¹ dla sceny ustawieñ.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan pocz¹tkowy sceny ustawieñ.
	 * @return `false`, jeœli inicjalizacja zakoñczy³a siê pomyœlnie, `true` w przypadku b³êdu.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê ustawieñ przed jej zniszczeniem.
	 */
	void cleanUp();
	/**
	 * @brief Zapisuje aktualnie ustawion¹ wartoœæ g³oœnoœci do pliku.
	 */
	void saveVolume();
	/**
	 * @brief Ustawia wskaŸnik do obiektu `sf::Music`, którego g³oœnoœæ jest kontrolowana.
	 * @param readMusic WskaŸnik na obiekt `sf::Music`.
	 */
	void setMusicPointer(sf::Music* readMusic);
};