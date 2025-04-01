#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

class ExitHandler {
	std::string getMessage(int exitCode);
	void saveToFile(std::string message);
	void printOut(std::string message);
public:
	void handleExitCode(int exitCode);
};