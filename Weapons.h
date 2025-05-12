#pragma once
#include "Items.h"
#include "Projectiles.h"

/**
* Wektor wektorów przechowuj¹cy bazowe statystyki dla ka¿dej broni.
* Kolejnoœæ statystyk w wewnêtrznym wektorze: OpóŸnienie Miêdzy Strza³ami, Obra¿enia, Prêdkoœæ Pocisku, Zasiêg.
*/
static std::vector<std::vector<float>> weaponBaseStats = {
	{20, 25, 3, 1000},   // Broñ 0
	{80, 500, 2, 1000},  // Broñ 1
	{30, 50, 3, 300},    // Broñ 2
	{50, 75, 7, 1000},   // Broñ 3
	{75, 300, 7, 400},   // Broñ 4
	{20, 200, 6, 1000},  // Broñ 5
	{20, 150, 5, 700},   // Broñ 6
	{15, 150, 6, 700},   // Broñ 7
	{45, 150, 8, 1000},  // Broñ 8
	{70, 500, 10, 1000}  // Broñ 9
};
/**
* Tablica flag wskazuj¹ca, czy dana broñ mo¿e ewoluowaæ.
*/
static bool weaponCanEvolve[10] = { true, true, true, true, true, false, true, false, false, false };
/**
* Tablica par przechowuj¹ca wymagania do ewolucji broni.
* Pierwszy element pary to identyfikator powsta³ej ewolucji, drugi to identyfikator wymaganego przedmiotu pasywnego.
*/
static std::pair<int, int> evolutionRequirement[10] = { {11, 7}, {11, 6}, {12, 8}, {14, 3}, {15, 5}, {0, 0}, {13, 12}, {0, 0}, {0, 0}, {0, 0} };
/**
 * @class Weapon
 * Klasa reprezentuj¹ca broñ posiadan¹ przez gracza, zarz¹dzaj¹ca jej statystykami,
 * poziomem, opóŸnieniem strza³u i potencjaln¹ ewolucj¹.
 */
class Weapon {
private: 
	/**
	* Podstawowe informacje o broni.
	*/
	ItemInfo basicInfo;
	/**
	* Bazowe opóŸnienie miêdzy kolejnymi atakami broni.
	*/
	int delay;
	/**
	* Aktualny licznik opóŸnienia do nastêpnego ataku.
	*/
	int currentDelay;
	/**
	* Identyfikator broni, w któr¹ ta broñ ewoluuje.
	*/
	int nextEvolution;
	/**
	* Identyfikator przedmiotu pasywnego wymaganego do ewolucji tej broni.
	*/
	int requiredItemId;
	/**
	* Bazowy zasiêg broni lub jej pocisków.
	*/
	int baseRange;
	/**
	* Bazowa wartoœæ obra¿eñ zadawanych przez broñ.
	*/
	float baseDmg;
	/**
	* Bazowa prêdkoœæ pocisków wystrzeliwanych przez broñ.
	*/
	float baseMs;
	/**
	* Flaga wskazuj¹ca, czy ta broñ mo¿e ewoluowaæ.
	*/
	bool canEvolve;
public:
	/**
	 * @brief Konstruktor domyœlny klasy Weapon.
	 */
	Weapon();
	/**
	 * @brief Ustawia statystyki broni na podstawie ustawionego id
	 */
	void setHidden();
	/**
	 * @brief Zwraca wskaŸnik do struktury przechowuj¹cej podstawowe informacje o przedmiocie.
	 * @return WskaŸnik do podstawowych informacji.
	 */
	ItemInfo* getBasicInfo();
	/**
	 * @brief Zmniejsza licznik aktualnego opóŸnienia do nastêpnego ataku.
	 */
	void decrementDelay();
	/**
	 * @brief Resetuje licznik aktualnego opóŸnienia do wartoœci bazowego opóŸnienia.
	 */
	void resetDelay();
	/**
	 * @brief Zwraca bazowe opóŸnienie miêdzy atakami tej broni.
	 * @return Bazowe opóŸnienie.
	 */
	int getDelay();
	/**
	 * @brief Zwraca informacjê, czy ta broñ mo¿e ewoluowaæ.
	 * @return Wartoœæ logiczna.
	 */
	bool getIfCanEvolve();
	/**
	 * @brief Zwraca identyfikator przedmiotu pasywnego wymaganego do ewolucji.
	 * @return Identyfikator wymaganego przedmiotu.
	 */
	int getRequiredItemEvolution();
	/**
	 * @brief Zwraca identyfikator broni, w któr¹ ta broñ ewoluuje.
	 * @return Identyfikator ewolucji.
	 */
	int getNextEvolution();
	/**
	 * @brief Resetuje stan broni.
	 */
	void reset();
	/**
	 * @brief Zwraca kontener przechowuj¹cy podstawowe statystyki broni.
	 * @return Kontener ze statystykami dla broni.
	 */
	std::vector<float> getStatsForProjectile();
	/**
	 * @brief Modyfikuje bazowe obra¿enia broni o podan¹ wartoœæ.
	 * @param readValue Wartoœæ, o któr¹ maj¹ zostaæ zmienione obra¿enia.
	 */
	void changeDamage(float readValue);
	/**
	 * @brief Modyfikuje bazowe opóŸnienie miêdzy atakami o podan¹ wartoœæ.
	 * @param readValue Wartoœæ, o któr¹ ma zostaæ zmienione opóŸnienie.
	 */
	void changeFirerate(int readValue);
	/**
	 * @brief Zwraca bazow¹ wartoœæ opóŸnienia.
	 * @return Bazowe opóŸnienie.
	 */
	int getBaseDelay();
};