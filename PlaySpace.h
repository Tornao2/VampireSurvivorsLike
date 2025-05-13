#pragma once
#include "Scene.h"
#include "CharacterData.h"

/**
 * @class PlaySpace
 * Klasa reprezentuj¹ca g³ówn¹ scenê rozgrywki.
 */
class PlaySpace : public Scene {
private:
	/**
	 * @brief Tablica pomocnicza do rozpraszania siê wrogów; dzieli planszê na 16x15 elementów
	 */
	bool enemyWiggleHelper[16][15];
	/**
	* @brief Indeks dla spritu gracza.
	*/
	int playerHolderIndex;
	/**
	* @brief Indeks dla elementów interfejsu u¿ytkownika.
	*/
	int hudHolderIndex;
	/**
	* @brief Indeks dla dodatkowego menu (pauzy, level-up).
	*/
	int additionalMenuIndex;
	/**
	* @brief Indeks wybranej mapy.
	*/
	int mapNumber;
	/**
	* @brief Indeks wybranej postaci.
	*/
	int charNumber;
	/**
	* @brief Czas ostatniego pojawienia siê przeciwnika.
	*/
	int lastSpawnTime = 10;
	/**
	* @brief Czas ostatniego wystrza³u broni.
	*/
	int lastFireTime = 0;
	/**
	* @brief Licznik odliczaj¹cy czas do mo¿liwoœci w³¹czenia/wy³¹czenia menu.
	*/
	int pauseBreak = 3;
	/**
	* @brief Indeks aktualnie wybranego przycisku w menu.
	*/
	int buttonIndex;
	/**
	* @brief Liczba dostêpnych wyborów podczas awansu na kolejny poziom.
	*/
	int availableChoices;
	/**
	* @brief Dodatkowe monety zebrane podczas bie¿¹cej sesji rozgrywki.
	*/
	int additionalCoins = 0;
	/**
	* @brief Ró¿nica poziomów po kalkulowaniu hp wrogów.
	*/
	int levelDifference = 0;
	/**
	* @brief Identyfikator pierwszej opcji wyboru podczas awansu na kolejny poziom.
	*/
	int choiceAId;
	/**
	* @brief Identyfikator drugiej opcji wyboru podczas awansu na kolejny poziom.
	*/
	int choiceBId;
	/**
	* @brief Flaga wskazuj¹ca, czy gra jest obecnie spauzowana.
	*/
	bool paused = false;
	/**
	* @brief Flaga wskazuj¹ca, czy aktywny jest ekran awansu na kolejny poziom.
	*/
	bool levelingUp = false;
	/**
	* @brief Flaga wskazuj¹ca, czy gracz wybiera podczas levelowania broñ.
	*/
	bool weaponTaking; 
	/**
	* @brief Obiekt przechowuj¹cy dane i statystyki postaci gracza.
	*/
	CharacterData playerData;
	/**
	* @brief Zegar u¿ywany do mierzenia czasu w grze.
	*/
	sf::Clock timer;
	/**
	 * @brief Okreœla wektor ruchu gracza na podstawie wejœcia.
	 * @return Wektor reprezentuj¹cy zamierzony ruch.
	 */
	sf::Vector2f determineMovement();
	/**
	 * @brief Obs³uguje kolizje gracza z terenem.
	 * @param moveStep Wektor ruchu, który ma zostaæ sprawdzony pod k¹tem kolizji.
	 */
	void terrainCollision(sf::Vector2f moveStep);
	/**
	 * @brief Zarz¹dza logik¹ ruchu gracza, ³¹cz¹c wykrywanie wejœcia i obs³ugê kolizji.
	 */
	void movementLogic();
	/**
	 * @brief Aktualizuje pozycje wszystkich aktywnych pocisków.
	 */
	void moveProjectiles();
	/**
	 * @brief Aktualizuje i wyœwietla czasomierz gry.
	 */
	void setTimer();
	/**
	 * @brief Zarz¹dza logik¹ fragmentów mapy.
	 */
	void chunkLogic();
	/**
	 * @brief Aktualizuje elementy interfejsu u¿ytkownika na podstawie stanu gry.
	 */
	void setHud();
	/**
	 * @brief Odpowiada za ponowne pojawianie siê przeciwników na mapie.
	 */
	void respawnEnemies();
	/**
	 * @brief Generuje losow¹ pozycjê na mapie.
	 * @return Wektor z losowymi wspó³rzêdnymi.
	 */
	sf::Vector2f randomizePos();
	/**
	 * @brief Sprawdza i obs³uguje kolizje miêdzy graczem a przeciwnikami.
	 */
	void checkEnemyCollision();
	/**
	 * @brief Aktualizuje pozycje wszystkich aktywnych przeciwników.
	 */
	void moveEnemies();
	/**
	 * @brief Sprawdza punkty ¿ycia przeciwników i obs³uguje ich œmieræ.
	 */
	void checkEnemyHp();
	/**
	 * @brief Zarz¹dza logik¹ broni gracza.
	 */
	void weaponLogic();
	/**
	 * @brief Sprawdza i obs³uguje kolizje pocisków z celami.
	 */
	void checkProjectileCollision();
	/**
	 * @brief Inicjalizuje elementy graficzne i logiczne menu pauzy.
	 */
	void initPauseMenu();
	/**
	 * @brief Zarz¹dza logik¹ power-upów.
	 */
	void powerUpLogic();
	/**
	 * @brief Aktywuje efekt wybranego power-upa.
	 * @param readId Identyfikator power-upa do aktywacji.
	 */
	void usePowerUp(int readId);
	/**
	 * @brief Zwalnia zasoby u¿ywane przez menu pauzy.
	 */
	void cleanPauseMenu();
	/**
	 * @brief Obs³uguje zmianê podœwietlenia przycisków w menu pauzy.
	 */
	void pauseButtonFocus();
	/**
	 * @brief Obs³uguje zmianê podœwietlenia przycisków w menu awansu na poziom.
	 */
	void levelButtonFocus();
	/**
	 * @brief Oblicza poœlizg gracza na œliskim terenie.
	 * @param readMovement Pierwotny wektor ruchu gracza.
	 */
	void calculateSlippage(sf::Vector2f readMovement);
	/**
	 * @brief Inicjalizuje ekran wyboru ulepszeñ podczas awansu na kolejny poziom.
	 * @return `false` jeœli inicjalizacja siê powiod³a, `true` w przeciwnym razie.
	 */
	bool initLevelUp();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez menu awansu na poziom.
	 */
	void cleanLevelMenu();
	/**
	 * @brief Decyduje, czy upuszczony przez przeciwnika przedmiot to broñ/przedmiot oraz iloœæ wyboru.
	 * @return `true` jeœli jest miejsce na kolejn¹ broñ/przedmiot, `false` w przeciwnym wypadku.
	 */
	bool getItemOrWeapon();
public:
	using Scene::Scene;
	/**
	 * @brief Ustawia numer wybranej mapy i postaci dla bie¿¹cej sesji gry.
	 * @param readMap Indeks wybranej mapy.
	 * @param readChar Indeks wybranej postaci.
	 */
	void setMapAndChar(int readMap, int readChar);
	/**
	 * @brief Przetwarza logikê zdarzeñ specyficzn¹ dla sceny rozgrywki.
	 * @param gameEvent Opcjonalne zdarzenie gry do przetworzenia.
	 * @return `false`, jeœli scena powinna kontynuowaæ dzia³anie, `true` w przeciwnym wypadku.
	 */
	bool eventLogic(std::optional<sf::Event> gameEvent);
	/**
	 * @brief Inicjalizuje zasoby i stan pocz¹tkowy sceny rozgrywki.
	 * @return `false`, jeœli inicjalizacja zakoñczy³a siê pomyœlnie, `true` w przypadku b³êdu.
	 */
	bool init();
	/**
	 * @brief Zwalnia zasoby u¿ywane przez scenê rozgrywki przed jej zniszczeniem.
	 */
	void cleanUp();
	/**
	 * @brief Wykonuje logikê gry, która powinna byæ aktualizowana w ka¿dej klatce niezale¿nie od zdarzeñ.
	 * @return `false` jeœli logika czasu rzeczywistego zosta³a przetworzona pomyœlnie i gra powinna kontynuowaæ, `true` w przypadku koñca gry.
	 */
	bool realTimeLogic();
	/**
	 * @brief Zwraca dane postaci gracza.
	 * @return Obiekt `CharacterData` z aktualnymi statystykami gracza.
	 */
	CharacterData getPlayerData();
	/**
	 * @brief Zwraca liczbê dodatkowych monet zebranych przez gracza w tej sesji.
	 * @return Liczba zebranych monet.
	 */
	int getCoins();
	/**
	 * @brief Sprawdza, czy powinna byæ wykonywana logika czasu rzeczywistego.
	 * @return `true`, jeœli pêtla gry ma kontynuowaæ, `false` w przeciwnym wypadku.
	 */
	bool getShouldRun();
	/**
	 * @brief Dekrementuje licznik czasu do odblokowania menu.
	 */
	void decrementPauseTime();
};