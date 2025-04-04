#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

class ExitHandler {
	std::string getMessage(int readExitCode);
	void saveToFile(std::string readMessage);
	void printToConsole(std::string readMessage);
public:
	void handleExitCode(int readExitCode);
};