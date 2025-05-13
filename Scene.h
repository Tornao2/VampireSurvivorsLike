#pragma once
#include "ObjectsHandler.h"
#include "Display.h"
#include "SoundManager.h"

/**
* Definicja koloru czerwonego.
*/
#define RED { 200, 10, 10}
/**
* Definicja koloru zielonego.
*/
#define GREEN { 40, 210, 40 }
/**
 * Definicja koloru niebieskiego.
 */
#define BLUE { 50, 90, 250 }
/**
* @enum SceneLabels
* @brief Etykiety identyfikuj¹ce poszczególne sceny w grze.
*/
enum SceneLabels {
	MAINMENU = 1,    ///< Etykieta sceny menu g³ównego.
	SETTINGS,        ///< Etykieta sceny ustawieñ.
	RESETCHOICE,     ///< Etykieta sceny potwierdzenia resetu.
	UPGRADE,         ///< Etykieta sceny ulepszeñ.
	PLAYCHOICE,      ///< Etykieta sceny wyboru postaci/mapy.
	PLAYSPACE,       ///< Etykieta sceny rozgrywki.
	FINISHSCREEN,    ///< Etykieta sceny ekranu koñcowego.
	GALLERY          ///< Etykieta sceny galerii.
};
/**
 * @class Scene
 * brief Abstrakcyjna klasa bazowa dla wszystkich scen w grze.
 */
class Scene {
protected:
	/**
	* @brief WskaŸnik do obiektu zarz¹dzaj¹cego obiektami w grze.
	*/
	ObjectsHandler* objectsHandler;
	/**
	* @brief WskaŸnik do zmiennej przechowuj¹cej etykietê aktualnej lub nastêpnej sceny.
	*/
	SceneLabels* sceneLabel;
	/**
	* @brief WskaŸnik do obiektu zarz¹dzaj¹cego dŸwiêkiem w grze.
	*/
	SoundManager* soundManager;
	/**
	* @brief WskaŸnik do zmiennej przechowuj¹cej aktualny poziom g³oœnoœci dŸwiêku.
	*/
	int* soundVolume;
public:
	/**
	 * @brief Konstruktor klasy Scene.
	 * @param readObjectsHandler WskaŸnik do `ObjectsHandler`.
	 * @param readLabel WskaŸnik do zmiennej przechowuj¹cej etykietê sceny.
	 * @param readManager WskaŸnik do `SoundManager`.
	 * @param volume WskaŸnik do zmiennej przechowuj¹cej poziom g³oœnoœci.
	 */
	Scene(ObjectsHandler* readObjectsHandler, SceneLabels* readLabel, SoundManager* readManager, int* volume) :
		objectsHandler(readObjectsHandler),
		sceneLabel(readLabel),
		soundManager(readManager),
		soundVolume(volume) {};
	/**
	 * @brief Wirtualna metoda obs³uguj¹ca logikê zdarzeñ specyficzn¹ dla danej sceny.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	virtual bool eventLogic(std::optional<sf::Event> gameEvent) = 0;
	/**
	 * @brief Wirtualna metoda inicjalizuj¹ca zasoby i stan sceny.
	 * @return `false`, jeœli inicjalizacja przebieg³a pomyœlnie, `true` w przypadku b³êdu.
	 */
	virtual bool init() = 0;
	/**
	 * @brief Wirtualna metoda zwalniaj¹ca zasoby u¿ywane przez scenê.
	 */
	virtual void cleanUp() = 0;
};