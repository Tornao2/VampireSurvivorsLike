#pragma once
#include "Modifiers.h"
#include "Unlocks.h"
#include "Weapons.h"

/**
 * @struct CharacterDetails
 * Struktura przechowuj¹ca bazowe statystyki i detale dla danego typu postaci.
 */
struct CharacterDetails {
	/**
	* Bazowa wartoœæ maksymalnego zdrowia.
	*/
	float baseHp;
	/**
	* Bazowa wartoœæ prêdkoœci poruszania siê.
	*/
	float baseMs;
	/**
	* Bazowy modyfikator obra¿eñ.
	*/
	float baseDamage;
	/**
	* Bazowy modyfikator zdobywanego doœwiadczenia.
	*/
	float baseExp;
	/**
	* Bazowa wartoœæ pancerza.
	*/
	int baseArmor;
	/**
	* Przesuniêcie grafiki postaci w pliku.
	*/
	sf::Vector2i offset;
};
/**
* Tablica przechowuj¹ca bazowe statystyki dla wszystkich dostêpnych postaci.
*/
static CharacterDetails charArray[NUMBEROFCHARS] = {
	{80.0f, 2.0f, 1.0f, 1.0f, 0, {0, 0}},    // Statystyki postaci 0
	{100.0f, 1.8f, 1.0f, 1.0f, 1, {16, 0}}, // Statystyki postaci 1
	{60.0f, 2.5f, 1.1f, 1.1f, 1, {32, 0}}, // Statystyki postaci 2
	{140.0f, 1.5f, 0.95f, 0.95f, 2, {48, 0}}  // Statystyki postaci 3
};

/**
 * @brief Zwraca bazowe statystyki dla postaci o podanym indeksie.
 * @param index Indeks postaci.
 * @return Struktura zawieraj¹ca bazowe statystyki postaci.
 */
CharacterDetails getCharacterStats(int index);

/**
 * @class CharacterData
 * Klasa przechowuj¹ca i zarz¹dzaj¹ca wszystkimi danymi dotycz¹cymi
 * aktualnego stanu postaci gracza w trakcie rozgrywki.
 */
class CharacterData {
private:
	/**
	* Aktualna pozycja postaci na mapie.
	*/
	sf::Vector2f pos;
	/**
	* Rozmiar postaci.
	*/
	sf::Vector2i size;
	/**
	* Modyfikator maksymalnego zdrowia wynikaj¹cy z ulepszeñ.
	*/
	float healthMod;
	/**
	* Modyfikator obra¿eñ wynikaj¹cy z ulepszeñ.
	*/
	float damageMod;
	/**
	* Modyfikator prêdkoœci poruszania siê wynikaj¹cy z ulepszeñ.
	*/
	float moveMod;
	/**
	* Modyfikator zdobywanego doœwiadczenia wynikaj¹cy z ulepszeñ.
	*/
	float expMod;
	/**
	* Modyfikator pancerza wynikaj¹cy z ulepszeñ.
	*/
	int armorMod;
	/**
	* Struktura przechowuj¹ca bazowe statystyki wybranej postaci.
	*/
	CharacterDetails baseStats;
	/**
	* Aktualna wartoœæ zdrowia postaci.
	*/
	float currentHp;
	/**
	* Aktualna iloœæ posiadanego doœwiadczenia.
	*/
	int xp;
	/**
	* Iloœæ doœwiadczenia wymagana do nastêpnego poziomu.
	*/
	int xpToNext;
	/**
	* Aktualny poziom postaci.
	*/
	int level;
	/**
	* Licznik klatek nietykalnoœci po otrzymaniu obra¿eñ.
	*/
	int invincibilityFrame;
	/**
	* Liczba aktualnie u¿ywanych slotów na broñ.
	*/
	int usedWeaponSlots = 3;
	/**
	* Kontener przechowuj¹cy informacje o posiadanych broniach.
	*/
	std::vector<Weapon> weaponInfo;
	/**
	* Kontener przechowuj¹cy informacje o posiadanych przedmiotach pasywnych.
	*/
	std::vector<ItemInfo> itemInfos;
	/**
	* Kontener flag wskazuj¹cych, czy dana broñ mo¿e ewoluowaæ.
	*/
	std::vector<bool> weaponCanEvolve = { false, false, false };
	/**
	* Wektor przechowuj¹cy aktualn¹ wartoœæ poœlizgu postaci.
	*/
	sf::Vector2f slippage;
	/**
	* Ostatni kierunek ruchu w osi X (true = prawo).
	*/
	bool lastXRight;
	/**
	* Ostatni kierunek ruchu w osi Y (true = dó³).
	*/
	bool lastYDown;
public:
	/**
	 * @brief Konstruktor klasy CharacterData. Inicjalizuje dane postaci.
	 */
	CharacterData();
	/**
	 * @brief Zwraca ostatni kierunek ruchu postaci w osi X.
	 * @return Kierunek X (prawda jeœli w prawo).
	 */
	bool getLastXDir();
	/**
	 * @brief Zwraca ostatni kierunek ruchu postaci w osi Y.
	 * @return Kierunek Y (prawda jeœli w dó³).
	 */
	bool getLastYDir();
	/**
	 * @brief Ustawia pozycjê i rozmiar postaci.
	 * @param readPos Nowa pozycja postaci.
	 * @param readSize Nowy rozmiar postaci.
	 */
	void setSizes(sf::Vector2f readPos, sf::Vector2i readSize);
	/**
	 * @brief Ustawia modyfikatory statystyk na podstawie pliku.
	 */
	void setMods();
	/**
	 * @brief Ustawia bazowe statystyki postaci na podstawie jej identyfikatora.
	 * @param charId Identyfikator wybranej postaci.
	 */
	void setBaseStats(int charId);
	/**
	 * @brief Przesuwa postaæ o podany wektor przesuniêcia.
	 * @param ms Wektor przesuniêcia.
	 */
	void move(sf::Vector2f ms);
	/**
	 * @brief Zwraca aktualn¹ pozycjê postaci.
	 * @return Aktualna pozycja.
	 */
	sf::Vector2f getPos();
	/**
	 * @brief Zwraca aktualn¹ wartoœæ zdrowia postaci.
	 * @return Aktualne zdrowie.
	 */
	float getCurrentHp();
	/**
	 * @brief Ustawia aktualn¹ wartoœæ zdrowia postaci.
	 * @param readHp Nowa wartoœæ zdrowia.
	 */
	void setHp(float readHp);
	/**
	 * @brief Zmienia aktualn¹ wartoœæ zdrowia postaci o podan¹ wartoœæ.
	 * @param readChange Wartoœæ zmiany zdrowia.
	 */
	void changeHp(float readChange);
	/**
	 * @brief Zwraca aktualn¹ iloœæ doœwiadczenia postaci.
	 * @return Iloœæ doœwiadczenia.
	 */
	int getXp();
	/**
	 * @brief Zwraca iloœæ doœwiadczenia wymagan¹ do nastêpnego poziomu.
	 * @return Wymagane doœwiadczenie.
	 */
	int getXpToNext();
	/**
	 * @brief Zwiêksza iloœæ doœwiadczenia postaci o podan¹ wartoœæ i obs³uguje awans na poziom.
	 * @param readXp Iloœæ zdobytego doœwiadczenia.
	 */
	void increaseXp(int readXp);
	/**
	 * @brief Zwraca aktualny poziom postaci.
	 * @return Poziom postaci.
	 */
	int getLevel();
	/**
	 * @brief Zwraca rozmiar postaci.
	 * @return Rozmiar postaci.
	 */
	sf::Vector2i getSize();
	/**
	 * @brief Zmniejsza licznik klatek nietykalnoœci.
	 */
	void decrementInvincibility();
	/**
	 * @brief Oblicza i zwraca efektywn¹ maksymaln¹ wartoœæ zdrowia postaci.
	 * @return Efektywne maksymalne zdrowie.
	 */
	float getEffectiveMaxHp();
	/**
	 * @brief Oblicza i zwraca efektywn¹ prêdkoœæ poruszania siê postaci.
	 * @return Efektywna prêdkoœæ poruszania.
	 */
	float getEffectiveMs();
	/**
	 * @brief Oblicza i zwraca efektywny modyfikator obra¿eñ postaci.
	 * @return Efektywny modyfikator obra¿eñ.
	 */
	float getEffectiveDamage();
	/**
	 * @brief Oblicza i zwraca efektywny modyfikator zdobywanego doœwiadczenia.
	 * @return Efektywny modyfikator doœwiadczenia.
	 */
	float getEffectiveXpMod();
	/**
	 * @brief Oblicza i zwraca efektywn¹ wartoœæ pancerza postaci.
	 * @return Efektywny pancerz.
	 */
	int getEffectiveArmorMod();
	/**
	 * @brief Zwraca przesuniêcie grafiki postaci.
	 * @return Przesuniêcie grafiki.
	 */
	sf::Vector2i getOffsets();
	/**
	 * @brief Ustawia aktualny wektor poœlizgu postaci.
	 * @param readSlipping Nowy wektor poœlizgu.
	 */
	void setSlippage(sf::Vector2f readSlipping);
	/**
	 * @brief Zwraca aktualny wektor poœlizgu postaci.
	 * @return Wektor poœlizgu.
	 */
	sf::Vector2f getSlippage();
	/**
	 * @brief Zwraca liczbê u¿ywanych slotów na broñ.
	 * @return Liczba u¿ywanych slotów na broñ.
	 */
	int getUsedWeaponSlots();
	/**
	 * @brief Zwraca liczbê u¿ywanych slotów na przedmioty pasywne.
	 * @return Liczba u¿ywanych slotów na przedmioty.
	 */
	int getUsedItemSlots();
	/**
	 * @brief Zwraca wskaŸnik do kontenera przechowuj¹cego informacje o broniach.
	 * @return WskaŸnik do kontenera broni.
	 */
	std::vector<Weapon>* getWeaponInfo();
	/**
	 * @brief Zwraca wskaŸnik do kontenera przechowuj¹cego informacje o przedmiotach pasywnych.
	 * @return WskaŸnik do kontenera przedmiotów.
	 */
	std::vector<ItemInfo>* getItemIds();
	/**
	 * @brief Zwraca kontener flag wskazuj¹cych, które bronie mog¹ ewoluowaæ.
	 * @return Kontener flag ewolucji broni.
	 */
	std::vector<bool> getIfEvolve();
	/**
	 * @brief Dodaje now¹ broñ do ekwipunku postaci lub zwiêksza jej poziom.
	 * @param readId Identyfikator dodawanej broni.
	 * @param readLevel Poziom dodawanej broni.
	 */
	void addWeapon(int readId, int readLevel);
	/**
	 * @brief Dodaje nowy przedmiot pasywny do ekwipunku postaci lub zwiêksza jego poziom.
	 * @param readId Identyfikator dodawanego przedmiotu.
	 * @param readLevel Poziom dodawanego przedmiotu.
	 */
	void addItem(int readId, int readLevel);
	/**
	 * @brief Zmienia statystyki postaci na podstawie dodanego przedmiotu pasywnego.
	 * @param readId Identyfikator przedmiotu.
	 * @param readLevel Poziom przedmiotu.
	 */
	void changeStats(int readId, int readLevel);
	/**
	 * @brief Zmienia statystyki konkretnej broni na podstawie jej poziomu i posiadanych przedmiotów pasywnych.
	 * @param readId Identyfikator broni.
	 * @param readLevel Poziom broni.
	 * @param readWeapon Referencja do obiektu broni, której statystyki maj¹ byæ zmienione.
	 */
	void changeWeaponStats(int readId, int readLevel, Weapon& readWeapon);
	/**
	 * @brief Zwraca liczbê posiadanych przedmiotów pasywnych.
	 * @return Liczba przedmiotów.
	 */
	int getHowManyItem();
	/**
	 * @brief Zwraca liczbê posiadanych broni.
	 * @return Liczba broni.
	 */
	int getHowManyWeapons();
	/**
	 * @brief Obs³uguje logikê otwierania skrzyni.
	 * @param readProjectileSprite WskaŸnik do tekstury pocisków.
	 */
	void chestLogic(sf::Texture* readProjectileSprite);
};
