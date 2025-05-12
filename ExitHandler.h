#pragma once
#include <iostream>
#include <filesystem> 
#include <string>
#include <fstream>

/**
 * @class ExitHandler
 * Klasa odpowiedzialna za obs³ugê kodów zakoñczenia programu,
 * generowanie odpowiednich komunikatów oraz ich zapisywanie lub wyœwietlanie.
 */
class ExitHandler {
private:
	/**
	 * @brief Metoda generuj¹ca komunikat tekstowy na podstawie podanego kodu wyjœcia.
	 * @param readExitCode Kod wyjœcia programu.
	 * @return Odpowiedni komunikat tekstowy jako std::string.
	 */
	std::string getMessage(int readExitCode);
	/**
	 * @brief Metoda zapisuj¹ca podany komunikat do pliku.
	 * @param readMessage Komunikat tekstowy do zapisania w pliku.
	 */
	void saveToFile(std::string readMessage);
	/**
	 * @brief Metoda wyœwietlaj¹ca podany komunikat na konsoli.
	 * @param readMessage Komunikat tekstowy do wyœwietlenia.
	 */
	void printToConsole(std::string readMessage);
public:
	/**
	 * @brief G³ówna metoda publiczna, która obs³uguje podany kod wyjœcia programu.
	 *        Pobiera odpowiedni komunikat, zapisuje go i wyœwietla.
	 * @param readExitCode Kod wyjœcia programu, który ma zostaæ obs³u¿ony.
	 */
	void handleExitCode(int readExitCode);
};