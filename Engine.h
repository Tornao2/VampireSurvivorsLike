#pragma once
#include "MainMenu.h"
#include "Settings.h"
#include "ResetChoice.h"
#include "UpgradeScene.h"
#include "PlayChoice.h"
#include "PlaySpace.h"
#include "FinishScreen.h"
#include "GalleryScene.h"

 /**
  * @class Engine
  * G³ówny obiekt aplikacji, odpowiedzialny za inicjalizacjê,
  * g³ówn¹ pêtlê gry, zarz¹dzanie scenami, obs³ugê zdarzeñ,
  * rysowanie oraz zarz¹dzanie dŸwiêkiem i stanem gry.
  */
class Engine {
private:
	/**
	* Etykieta identyfikuj¹ca aktualnie aktywn¹ scenê gry.
	*/
	SceneLabels sceneLabel;
	/**
	* Obiekt klasy Display, zarz¹dzaj¹cy oknem i parametrami wyœwietlania.
	*/
	Display display;
	/**
	* Obiekt klasy ObjectsHandler, zarz¹dzaj¹cy obiektami w grze.
	*/
	ObjectsHandler objectsHandler;
	/*
	* WskaŸnik do aktualnie za³adowanej i aktywnej sceny.
	*/
	Scene* scene;
	/**
	* Obiekt klasy SoundManager, odpowiedzialny za zarz¹dzanie efektami dŸwiêkowymi i muzyk¹.
	*/
	SoundManager soundManager;
	/**
	* Obiekt do odtwarzania muzyki t³a.
	*/
	sf::Music playedMusic;
	/**
	* Nazwa pliku aktualnie odtwarzanej muzyki.
	*/
	std::string currentMusic;
	/**
	* Aktualny poziom g³oœnoœci dŸwiêków.
	*/
	int soundVolume;
	/**
	 * @brief Metoda wczytuj¹ca poziom g³oœnoœci z pliku konfiguracyjnego.
	 */
	void loadVolume();
	/**
	 * @brief Metoda odpowiedzialna za rysowanie zawartoœci aktualnej sceny w oknie.
	 */
	void draw();
	/**
	 * @brief Metoda obs³uguj¹ca zdarzenia.
	 */
	void handleEvents();
	/**
	 * @brief Metoda zarz¹dzaj¹ca logik¹ zmiany sceny.
	 */
	void changeScene();
	/**
	 * @brief Metoda pomocnicza specyficzna dla rysowania sceny gry PlaySpace na podanej teksturze.
	 * @param texture WskaŸnik do tekstury sf::RenderTexture, na której ma byæ narysowana scena gry.
	 */
	void drawPlayScene(sf::RenderTexture* texture);
	/**
	 * @brief £aduje i rozpoczyna odtwarzanie muzyki z podanego pliku.
	 * @param filename Nazwa pliku muzycznego.
	 */
	void loadMusic(std::string filename);
	/**
	* Przechowuje kod b³êdu, jeœli wyst¹pi³ jakiœ problem podczas dzia³ania silnika.
	*/
	int errorCode;
	/**
	* Indeks wybranej przez gracza mapy.
	*/
	int selectedMap;
	/**
	* Indeks wybranej przez gracza postaci.
	*/
	int selectedChar;
	/**
	* Zmienna tymczasowa do przekazywania danych miêdzy scenami.
	*/
	int tempVariable;
public:
	/**
	 * @brief Konstruktor domyœlny klasy Engine. Odpowiada za inicjalizacjê silnika.
	 */
	Engine();
	/**
	 * @brief G³ówna pêtla gry.
	 * Odpowiada za cykliczne wywo³ywanie obs³ugi zdarzeñ, aktualizacji logiki i rysowania.
	 */
	void mainLoop();
	/**
	 * @brief Zwraca kod b³êdu, który wyst¹pi³ podczas dzia³ania silnika.
	 * @return Liczba ca³kowita reprezentuj¹ca kod b³êdu. 0 oznacza brak b³êdu.
	 */
	int getErrorCode();
};