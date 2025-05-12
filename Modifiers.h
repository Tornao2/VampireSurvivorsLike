#pragma once
#include <vector>
#include <fstream>
#include <sstream>

/**
 * @struct ModifierNode
 * Struktura reprezentuj¹ca pojedynczy modyfikator w grze,
 * przechowuj¹ca jego nazwê, poziom i si³ê efektu.
 */
struct ModifierNode {
	/**
	* Nazwa identyfikuj¹ca modyfikator.
	*/
	std::string name = "";
	/**
	* Aktualny poziom ulepszenia modyfikatora.
	*/
	int currentLevel;
	/**
	* Maksymalny mo¿liwy poziom ulepszenia modyfikatora.
	*/
	int maxLevel;
	/**
	* Wartoœæ okreœlaj¹ca si³ê efektu modyfikatora.
	*/
	float effectStrength;
};
/**
 * @class Modifiers
 * Klasa zarz¹dzaj¹ca systemem modyfikatorów w grze.
 */
class Modifiers {
private:
	/**
	* G³ówny kontener przechowuj¹cy wszystkie dostêpne modyfikatory.
	*/
	std::vector <ModifierNode> modVector;
	/**
	* Aktualna liczba posiadanych przez gracza monet do wydania na modyfikatory.
	*/
	int coins = 0;
	/**
	 * @brief Wczytuje domyœln¹ konfiguracjê modyfikatorów.
	 */
	void loadCleanModifiers();
public:
	/**
	 * @brief Wczytuje stan modyfikatorów z pliku zapisu.
	 */
	void loadModifiersFromFile();
	/**
	 * @brief Zapisuje aktualny stan modyfikatorów do pliku.
	 */
	void saveModifiersToFile();
	/**
	 * @brief Zwraca wskaŸnik do wêz³a modyfikatora o podanej nazwie.
	 * @param readName Nazwa szukanego modyfikatora.
	 * @return WskaŸnik do znalezionego wêz³a modyfikatora.
	 */
	ModifierNode* getNodeByName(std::string readName);
	/**
	 * @brief Zwraca wskaŸnik do g³ównego kontenera przechowuj¹cego modyfikatory.
	 * @return WskaŸnik do kontenera modyfikatorów.
	 */
	std::vector<ModifierNode>* getVector();
	/**
	 * @brief Zwraca tekstow¹ reprezentacjê si³y efektu modyfikatora o podanym indeksie.
	 * @param readIndex Indeks modyfikatora w kontenerze.
	 * @return Tekstowa reprezentacja si³y efektu.
	 */
	std::string getModStrength(int readIndex);
	/**
	 * @brief Zwraca tekstow¹ reprezentacjê poziomu modyfikatora o podanym indeksie.
	 * @param readIndex Indeks modyfikatora w kontenerze.
	 * @return Tekstowa reprezentacja poziomu.
	 */
	std::string getModLevel(int readIndex);
	/**
	 * @brief Zwraca tekstow¹ reprezentacjê aktualnej liczby posiadanych monet.
	 * @return Tekstowa reprezentacja liczby monet.
	 */
	std::string getCoins();
	/**
	 * @brief Zwraca tablicê okreœlaj¹c¹ liczbê modyfikatorów w ka¿dej kolumnie.
	 * @return WskaŸnik na tablicê z liczb¹ modyfikatorów w kolumnach.
	 */
	unsigned char* getColumnAmounts();
	/**
	 * @brief Zwraca liczbê rzêdów modyfikatorów.
	 * @return Liczba rzêdów.
	 */
	unsigned char getRowAmount();
	/**
	 * @brief Próbuje zwiêkszyæ poziom modyfikatora o podanym indeksie, jeœli gracz ma wystarczaj¹co monet.
	 * @param index Indeks modyfikatora do ulepszenia.
	 * @return Wartoœæ logiczna wskazuj¹ca, czy ulepszenie siê powiod³o.
	 */
	bool increaseLevel(int index);
	/**
	 * @brief Zmienia liczbê posiadanych monet o podan¹ wartoœæ.
	 * @param readCoinChange Wartoœæ, o któr¹ ma zostaæ zmieniona liczba monet.
	 */
	void changeCoins(int readCoinChange);
};