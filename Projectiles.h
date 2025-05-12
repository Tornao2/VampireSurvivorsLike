#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Projectiles
 * Klasa reprezentuj¹ca pojedynczy pocisk wystrzelony przez broñ.
 */
class Projectiles {
private:
	/**
	* WskaŸnik do obiektu graficznego reprezentuj¹cego pocisk.
	*/
	sf::Sprite* sprite = nullptr;
	/**
	* Efektywna wartoœæ obra¿eñ zadawanych przez pocisk.
	*/
	float effectiveDamage;
	/**
	* Efektywny zasiêg pocisku.
	*/
	float effectiveRange;
	/**
	* Aktualny wektor prêdkoœci pocisku.
	*/
	sf::Vector2f actualMs;
	/**
	* Rozmiar pocisku.
	*/
	sf::Vector2i size;
	/**
	* Aktualna pozycja pocisku na mapie.
	*/
	sf::Vector2f pos;
public:
	/**
	 * @brief Konstruktor klasy Projectiles.
	 * @param readSprite WskaŸnik do obiektu graficznego dla tego pocisku.
	 * @param damage Wartoœæ obra¿eñ pocisku.
	 * @param range Zasiêg pocisku.
	 * @param ms Prêdkoœæ pocisku.
	 * @param readPos Pozycja pocz¹tkowa pocisku.
	 * @param readEndPos Pozycja docelowa pocisku.
	 * @param readSize Rozmiar pocisku.
	 */
	Projectiles(sf::Sprite* readSprite, float damage, float range, float ms, sf::Vector2f readPos, sf::Vector2f readEndPos, sf::Vector2i readSize);
	/**
	 * @brief Zwraca rozmiar pocisku.
	 * @return Rozmiar pocisku.
	 */
	sf::Vector2i getSize();
	/**
	 * @brief Zwraca aktualn¹ pozycjê pocisku.
	 * @return Aktualna pozycja.
	 */
	sf::Vector2f getPos();
	/**
	 * @brief Zwraca efektywn¹ wartoœæ obra¿eñ zadawanych przez pocisk.
	 * @return Wartoœæ obra¿eñ.
	 */
	float getDamage();
	/**
	 * @brief Usuwa powi¹zanie ze sprite'em.
	 */
	void clearSprite();
	/**
	 * @brief Przesuwa pocisk zgodnie z jego aktualnym wektorem prêdkoœci i zmniejsza pozosta³y zasiêg.
	 */
	void move();

	/**
	 * @brief Zwraca wskaŸnik do obiektu graficznego pocisku.
	 * @return WskaŸnik do obiektu graficznego.
	 */
	sf::Sprite* getSprite();
	/**
	 * @brief Obraca pocisk w kierunku podanej pozycji docelowej.
	 * @param readTargetPos Pozycja celu, w kierunku którego pocisk ma siê obróciæ.
	 * @param readMs Prêdkoœæ.
	 */
	void rotate(sf::Vector2f readTargetPos, float readMs);
};