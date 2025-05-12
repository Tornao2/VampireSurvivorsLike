#pragma once
#include <SFML/Graphics.hpp>

/**
 * @struct EnemyDataNode
 * Struktura przechowuj¹ca bazowe statystyki dla danego typu przeciwnika.
 */
struct EnemyDataNode {
	/**
	* Przesuniêcie grafiki przeciwnika wzglêdem w pliku.
	*/
	sf::Vector2i offset;
	/**
	* Bazowa wartoœæ pancerza.
	*/
	int armor;
	/**
	* Iloœæ doœwiadczenia przyznawana za pokonanie przeciwnika.
	*/
	int xp;
	/**
	* Bazowa wartoœæ maksymalnego zdrowia.
	*/
	float baseHp;
	/**
	* Bazowa wartoœæ obra¿eñ zadawanych przez przeciwnika.
	*/
	float damage;
	/**
	* Bazowa wartoœæ prêdkoœci poruszania siê przeciwnika.
	*/
	float move;
};
/**
* Tablica przechowuj¹ca bazowe statystyki dla wszystkich typów przeciwników.
*/
static EnemyDataNode enemyArray[] = {
	{{0, 0}, 0, 10, 70,  8, 0.7f}, // Statystyki przeciwnika typu 0
	{{16, 0}, 5, 11, 100,  8, 0.7f}, // Statystyki przeciwnika typu 1
	{{32, 0}, 5, 11, 120, 11, 0.8f}, // Statystyki przeciwnika typu 2
	{{48, 0}, 10, 12, 140, 11, 1.0f}, // Statystyki przeciwnika typu 3
	{{64, 0}, 12, 13, 80, 14, 0.9f}, // Statystyki przeciwnika typu 4
	{{0, 24},  14, 14, 110, 14, 0.7f}, // Statystyki przeciwnika typu 5
	{{16, 24}, 15, 15, 180, 14, 1.0f}, // Statystyki przeciwnika typu 6
	{{32, 24}, 15, 16, 190,  11, 1.0f}, // Statystyki przeciwnika typu 7
	{{48, 24},  0, 20, 170, 10, 1.1f}, // Statystyki przeciwnika typu 8
	{{64, 24}, 15, 22, 100, 15, 1.2f}  // Statystyki przeciwnika typu 9
};
/**
 * @class EnemyData
 * Klasa przechowuj¹ca i zarz¹dzaj¹ca danymi pojedynczego przeciwnika.
 */
class EnemyData {
private:
	/**
	* Aktualna pozycja przeciwnika na mapie.
	*/
	sf::Vector2f pos;
	/**
	* Rozmiar przeciwnika.
	*/
	sf::Vector2f size;
	/**
	* Aktualna wartoœæ zdrowia przeciwnika.
	*/
	float currentHp;
	/**
	* Struktura przechowuj¹ca bazowe statystyki tego typu przeciwnika.
	*/
	EnemyDataNode enemyStats;
	/**
	* WskaŸnik do obiektu graficznego reprezentuj¹cego przeciwnika.
	*/
	sf::Sprite* sprite;
	/**
	* Flaga wskazuj¹ca, czy ten przeciwnik jest bossem.
	*/
	bool isBoss;
public:
	/**
	 * @brief Inicjalizuje dane przeciwnika na podstawie jego typu i pozycji.
	 * @param enemyId Identyfikator typu przeciwnika.
	 * @param readPos Pozycja pocz¹tkowa przeciwnika.
	 * @param readIsBoss Flaga wskazuj¹ca, czy przeciwnik jest bossem.
	 */
	void giveStats(int enemyId, sf::Vector2f readPos, bool readIsBoss);
	/**
	 * @brief Zwraca rozmiar przeciwnika.
	 * @return Rozmiar przeciwnika.
	 */
	sf::Vector2f getSize();
	/**
	 * @brief Zwraca aktualn¹ pozycjê przeciwnika.
	 * @return Aktualna pozycja.
	 */
	sf::Vector2f getPos();
	/**
	 * @brief Zwraca wartoœæ obra¿eñ zadawanych przez przeciwnika.
	 * @return Wartoœæ obra¿eñ.
	 */
	float getDamage();
	/**
	 * @brief Przesuwa przeciwnika o podany wektor przesuniêcia.
	 * @param ms Wektor przesuniêcia.
	 */
	void move(sf::Vector2f ms);
	/**
	 * @brief Zmienia aktualne zdrowie przeciwnika o podan¹ wartoœæ.
	 * @param readChange Wartoœæ zmiany zdrowia.
	 */
	void changeHealthBy(float readChange);
	/**
	 * @brief Zwraca aktualn¹ wartoœæ zdrowia przeciwnika.
	 * @return Aktualne zdrowie.
	 */
	float getHealth();
	/**
	 * @brief Usuwa powi¹zanie ze sprite'em.
	 */
	void clearSprite();
	/**
	 * @brief Zwraca wskaŸnik do obiektu graficznego przeciwnika.
	 * @return WskaŸnik do obiektu graficznego.
	 */
	sf::Sprite* getSprite();
	/**
	 * @brief Ustawia wskaŸnik do obiektu graficznego reprezentuj¹cego przeciwnika.
	 * @param readSprite WskaŸnik do obiektu graficznego.
	 */
	void setSprite(sf::Sprite* readSprite);
	/**
	 * @brief Zwraca iloœæ doœwiadczenia przyznawan¹ za pokonanie tego przeciwnika.
	 * @return Iloœæ doœwiadczenia.
	 */
	int getXpForKill();
	/**
	 * @brief Zwraca informacjê, czy przeciwnik jest bossem.
	 * @return Wartoœæ logiczna (prawda jeœli boss).
	 */
	bool getIfBoss();
	/**
	 * @brief Ustawia now¹ pozycjê przeciwnika.
	 * @param readPosition Nowa pozycja.
	 */
	void setPosition(sf::Vector2f readPosition);
	/**
	 * @brief Zwraca przesuniêcie grafiki przeciwnika.
	 * @return Przesuniêcie grafiki.
	 */
	sf::Vector2i getOffset();
};
