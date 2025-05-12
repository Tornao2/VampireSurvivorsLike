#pragma once
#include <SFML/Graphics.hpp>
#include <fstream> 
/**
* Domyœlna szerokoœæ sceny renderowania.
*/
#define SCENEWIDTH 432
/**
* Domyœlna wysokoœæ sceny renderowania.
*/
#define SCENEHEIGHT 270
/**
 * @enum DisplayMode
 * @brief Wyliczenie okreœlaj¹ce mo¿liwe tryby wyœwietlania okna aplikacji.
 */
enum DisplayMode {
	/**
	* Tryb okienkowy
	*/
	windowed, 
	/**
	* Tryb pe³noekranowy
	*/
	full,     
	/**
	* Tryb pe³noekranowy z czarn¹ obramówk¹
	*/
	borders   
};
/**
 * @class Display
 * Odpowiada za tworzenie i konfiguracjê okienka,
 * zarz¹dzanie widokiem oraz zapisywanie i wczytywanie
 * ustawieñ wyœwietlania z pliku.
 */
class Display {
private:
	/**
	* Aktualny rozmiar okna aplikacji
	*/
	sf::Vector2f windowSize;
	/**
	* Aktualnie ustawiony tryb wyœwietlania
	*/
	DisplayMode fullscreenMode;
	/**
	* Widok u¿ywany do prawid³owego skalowania i pozycjonowania obrazu
	*/
	sf::View screenView;
	/**
	* G³ówna instancja okna renderowania
	*/
	sf::RenderWindow windowInstance;
	/**
	 * @brief Metoda do ponownego tworzenia lub konfiguracji okna i widoku.
	 */
	void recalibrateWindow();
public:
	/**
	 * @brief Konstruktor domyœlny klasy Display.
	 */
	Display();
	/**
	 * @brief Ustawia now¹ rozdzielczoœæ okna.
	 * @param readResolution Nowy rozmiar okna
	 */
	void setResolution(sf::Vector2f readResolution);
	/**
	 * @brief Zwraca wskaŸnik do instancji okna
	 * @return WskaŸnik do obiektu `sf::RenderWindow`.
	 */
	sf::RenderWindow* getWindow();
	/**
	 * @brief Ustawia tryb wyœwietlania okna (okienkowy, pe³noekranowy, bez ramek).
	 * @param readFullscreenMode Nowy tryb wyœwietlania.
	 */
	void setFullscreen(DisplayMode readFullscreenMode);
	/**
	 * @brief Zwraca aktualny rozmiar okna.
	 * @return Aktualny rozmiar okna.
	 */
	sf::Vector2f getWindowSize();
	/**
	 * @brief Zwraca aktualny tryb wyœwietlania okna.
	 * @return Aktualny tryb wyœwietlania.
	 */
	DisplayMode getFullscreen();
	/**
	 * @brief Wczytuje konfiguracjê wyœwietlania z pliku.
	 */
	void loadFromFile();
	/**
	 * @brief Zapisuje aktualn¹ konfiguracjê wyœwietlania do pliku.
	 */
	void saveToFile();
};