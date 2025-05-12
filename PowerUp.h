#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

/**
 * @class PowerUp
 * Klasa reprezentuj¹ca pojedynczy obiekt power-upu.
 */
class PowerUp {
private: 
	/**
	* Identyfikator typu power-upu.
	*/
	int id;
	/**
	* WskaŸnik do obiektu graficznego reprezentuj¹cego power-up.
	*/
	sf::Sprite* sprite;
	/**
	* Aktualna pozycja power-upu na mapie.
	*/
	sf::Vector2f position;
	/**
	* Rozmiar power-upu.
	*/
	sf::Vector2i size;
	/**
	* Pozosta³y czas istnienia power-upu na mapie (w klatkach).
	*/
	int timeLeft;
public:
	/**
	 * @brief Konstruktor klasy PowerUp.
	 * @param readId Identyfikator tworzonego power-upu.
	 * @param readPosition Pozycja pocz¹tkowa power-upu.
	 * @param readSprite WskaŸnik do obiektu graficznego dla tego power-upu.
	 */
	PowerUp(int readId, sf::Vector2f readPosition, sf::Sprite* readSprite);
	/**
	 * @brief Zwraca identyfikator typu tego power-upu.
	 * @return Identyfikator typu.
	 */
	int getId();
	/**
	 * @brief Zmniejsza licznik pozosta³ego czasu istnienia power-upu.
	 * @return Wartoœæ logiczna wskazuj¹ca, czy czas siê skoñczy³.
	 */
	bool decrementTimeLeft();
	/**
	 * @brief Zwraca rozmiar power-upu.
	 * @return Rozmiar power-upu.
	 */
	sf::Vector2i getSize();
	/**
	 * @brief Zwraca aktualn¹ pozycjê power-upu.
	 * @return Aktualna pozycja.
	 */
	sf::Vector2f getPos();
	/**
	 * @brief Zwraca wskaŸnik do obiektu graficznego power-upu.
	 * @return WskaŸnik do obiektu graficznego.
	 */
	sf::Sprite* getSprite();
	/**
	 * @brief Usuwa powi¹zanie ze sprite'em.
	 */
	void deleteSprite();
};