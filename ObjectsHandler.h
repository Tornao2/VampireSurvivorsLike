#pragma once
#include "MapGenerator.h"
#include "EnemyData.h"
#include "Projectiles.h"
#include "PowerUp.h"
#include "Weapons.h"

/**
 * @class ObjectsHandler
 * Centralna klasa zarz¹dzaj¹ca wszystkimi obiektami w grze.
 */
class ObjectsHandler {
private:
	/**
	* Czcionka u¿ywana do renderowania tekstu w grze.
	*/
	sf::Font font;
	/**
	* Kontener przechowuj¹cy obiekty tekstowe.
	*/
	std::vector <sf::Text> textHolder; 
	/**
	* Kontener przechowuj¹cy wskaŸniki do danych przeciwników.
	*/
	std::list <EnemyData*> enemyHolder; 
	/**
	* Kontener przechowuj¹cy wskaŸniki do wektorów wskaŸników na sprite'y.
	*/
	std::vector <std::vector<sf::Sprite>*> spriteHolder; 
	/**
	* Kontener przechowuj¹cy wskaŸniki do obiektów pocisków.
	*/
	std::list <Projectiles*> projectileHolder; 
	/**
	* Kontener przechowuj¹cy wskaŸniki do obiektów power-upów PowerUp.
	*/
	std::list <PowerUp*> powerUpHolder; 
	/**
	* Mapa przechowuj¹ca za³adowane tekstury sf::Texture.
	*/
	std::unordered_map<std::string, sf::Texture> textureHolder; 
	/**
	* Instancja generatora mapy.
	*/
	MapGenerator generator;
	/**
	 * @brief Znajduje i zwraca wspó³rzêdne najbli¿szego przeciwnika wzglêdem podanej pozycji gracza.
	 * @param readPlayerPos Aktualna pozycja gracza.
	 * @return Wspó³rzêdne najbli¿szego przeciwnika.
	 */
	sf::Vector2f getClosestEnemyCords(sf::Vector2f readPlayerPos);
	/**
	 * @brief Zwraca losowe wspó³rzêdne jednego z istniej¹cych przeciwników.
	 * @return Losowe wspó³rzêdne przeciwnika.
	 */
	sf::Vector2f getRandomEnemyCords(); 
public:
	/**
	 * @brief Konstruktor klasy ObjectsHandler. Inicjalizuje kontenery i zasoby.
	 */
	ObjectsHandler();
	/**
	 * @brief £aduje teksturê z pliku, jeœli jeszcze nie zosta³a za³adowana, i zwraca na ni¹ wskaŸnik.
	 * @param size Rozmiar tekstury.
	 * @param fileName Nazwa pliku tekstury do za³adowania.
	 * @return WskaŸnik do za³adowanej tekstury.
	 */
	sf::Texture* loadTexture(sf::Vector2i size, std::string fileName);
	/**
	 * @brief Tworzy sprite'a na podstawie podanej tekstury i dodaje go do okreœlonej kolekcji w spriteHolder.
	 * @param texture Referencja do tekstury, która ma byæ u¿yta dla sprite'a.
	 * @param size Rozmiar obszaru tekstury do u¿ycia.
	 * @param position Pozycja pocz¹tkowa sprite'a na ekranie.
	 * @param index Indeks kolekcji w spriteHolder, do której sprite ma zostaæ dodany.
	 */
	void loadSpriteIntoHolder(sf::Texture& texture, sf::Vector2i size, sf::Vector2i position, int index);
	/**
	 * @brief Dodaje nowy pusty wektor do spriteHolder.
	 * @return Indeks nowo dodanej kolekcji.
	 */
	int addVectorToSpriteHolder();
	/**
	 * @brief Usuwa wszystkie kolekcje i sprite'y ze spriteHolder, zwalniaj¹c pamiêæ.
	 */
	void clearSpriteHolder();
	/**
	 * @brief Zwraca wskaŸnik do g³ównego kontenera spriteHolder.
	 * @return WskaŸnik do g³ównego kontenera spriteHolder.
	 */
	std::vector <std::vector<sf::Sprite>*>* getSpriteHolder(); 
	/**
	 * @brief Zwraca wskaŸnik do konkretnego sprite'a w okreœlonej kolekcji.
	 * @param collectionIndex Indeks kolekcji w spriteHolder.
	 * @param spriteIndex Indeks sprite'a wewn¹trz kolekcji.
	 * @return WskaŸnik do sprite'a.
	 */
	sf::Sprite* getSpritePointer(int collectionIndex, int spriteIndex); 
	/**
	 * @brief Zwraca liczbê sprite'ów w okreœlonej kolekcji.
	 * @param collectionIndex Indeks kolekcji w spriteHolder.
	 * @return Liczba sprite'ów w kolekcji.
	 */
	int getSpriteHolderSize(int collectionIndex);
	/**
	 * @brief Zwraca wskaŸnik do kontenera przechowuj¹cego teksty.
	 * @return WskaŸnik do kontenera przechowuj¹cego teksty.
	 */
	std::vector <sf::Text>* getTextHolder(); 
	/**
	 * @brief Zwraca wskaŸnik do konkretnego obiektu tekstowego.
	 * @param textIndex Indeks tekstu w textHolder.
	 * @return WskaŸnik do tekstu.
	 */
	sf::Text* getTextPointer(int textIndex);
	/**
	 * @brief Usuwa wszystkie teksty z textHolder.
	 */
	void clearTextHolder();
	/**
	 * @brief Tworzy nowy obiekt tekstowy i dodaje go do textHolder.
	 * @param readText Tekst do wyœwietlenia.
	 * @param size Rozmiar czcionki.
	 * @param position Pozycja tekstu na ekranie.
	 */
	void loadTextIntoHolder(std::string readText, unsigned char size, sf::Vector2f position);
	/**
	 * @brief Oblicza szerokoœæ renderowanego tekstu dla podanych parametrów.
	 * @param readText Tekst, którego szerokoœæ ma byæ obliczona.
	 * @param size Rozmiar czcionki.
	 * @return Szerokoœæ tekstu w pikselach.
	 */
	float calculateTextWidth(std::string readText, unsigned char size); 
	/**
	 * @brief Dodaje nowego przeciwnika do enemyHolder.
	 * @param enemyId Identyfikator typu przeciwnika.
	 * @param readPos Pozycja pocz¹tkowa przeciwnika.
	 * @param readIsBoss Flaga wskazuj¹ca, czy przeciwnik jest bossem.
	 */
	void addEnemy(int enemyId, sf::Vector2f readPos, bool readIsBoss); 
	/**
	 * @brief Usuwa wszystkich przeciwników z enemyHolder, zwalniaj¹c pamiêæ.
	 */
	void clearEnemyHolder();
	/**
	 * @brief Zwraca wskaŸnik do kontenera przechowuj¹cego dane przeciwników.
	 * @return WskaŸnik do kontenera przechowuj¹cego dane przeciwników.
	 */
	std::list <EnemyData*>* getEnemyHolder(); 
	/**
	 * @brief Usuwa okreœlon¹ listê przeciwników z enemyHolder.
	 * @param enemiesToKill Lista wskaŸników do przeciwników, którzy maj¹ zostaæ usuniêci.
	 */
	void killEnemy(std::list<EnemyData*> enemiesToKill);
	/**
	 * @brief Dodaje nowy pocisk do projectileHolder.
	 * @param weapon Obiekt broni, z której wystrzelono pocisk.
	 * @param readPos Pozycja pocz¹tkowa pocisku.
	 * @param faceRight Kierunek poziomy pocisku.
	 * @param faceDown Kierunek pionowy pocisku.
	 */
	void addProjectile(Weapon weapon, sf::Vector2f readPos, bool faceRight, bool faceDown);
	/**
	 * @brief Usuwa wszystkie pociski z projectileHolder, zwalniaj¹c pamiêæ.
	 */
	void clearProjectileHolder();
	/**
	 * @brief Zwraca wskaŸnik do kontenera przechowuj¹cego pociski.
	 * @return WskaŸnik do kontenera przechowuj¹cego pociski.
	 */
	std::list <Projectiles*>* getProjectileHolder();
	/**
	 * @brief Usuwa okreœlon¹ listê pocisków z projectileHolder.
	 * @param projectilesToDestroy Lista wskaŸników do pocisków, które maj¹ zostaæ usuniête.
	 */
	void destroyProjectiles(std::list<Projectiles*> projectilesToDestroy); 
	/**
	 * @brief Dodaje nowy power-up do powerUpHolder.
	 * @param powerUpId Identyfikator typu power-upu.
	 * @param readPos Pozycja pocz¹tkowa power-upu.
	 */
	void addPowerUp(int powerUpId, sf::Vector2f readPos);
	/**
	 * @brief Usuwa wszystkie power-upy z powerUpHolder, zwalniaj¹c pamiêæ.
	 */
	void clearPowerUpHolder();
	/**
	 * @brief Zwraca wskaŸnik do kontenera przechowuj¹cego power-upy.
	 * @return WskaŸnik do kontenera przechowuj¹cego power-upy.
	 */
	std::list <PowerUp*>* getPowerUpHolder(); 
	/**
	 * @brief Usuwa okreœlony power-up z powerUpHolder.
	 * @param powerUpToDestroy WskaŸnik do power-upu, który ma zostaæ usuniêty.
	 */
	void destroyPowerUp(PowerUp* powerUpToDestroy);
	/**
	 * @brief Zwraca wskaŸnik do instancji generatora mapy.
	 * @return WskaŸnik do obiektu MapGenerator.
	 */
	MapGenerator* getMapGenerator();
	/**
	 * @brief Ustawia mapê o podanym identyfikatorze w generatorze mapy.
	 * @param readMapId Identyfikator mapy do ustawienia.
	 */
	void setMap(int readMapId);
	/**
	 * @brief Oblicza i zwraca prostok¹t definiuj¹cy obszar sprite'a dla pocisku o danym ID.
	 * @param readId Identyfikator pocisku.
	 * @return sf::IntRect okreœlaj¹cy pozycjê i rozmiar klatki sprite'a pocisku.
	 */
	sf::IntRect calcProjectileSpriteData(int readId);
};