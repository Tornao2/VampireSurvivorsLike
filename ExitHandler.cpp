#include "ExitHandler.h"

std::string ExitHandler::getMessage(int exitCode) {
	switch (exitCode) {
		case -1:
			return "Failed in loading font";
		case 1:
			return "Failed in loading mainmenu textures";
		case 2:
			return "Failed in loading settings textures";
		case 3:
			return "Failed in loading resetchoice textures";
		case 4:
			return "Failed in loading upgrade textures";
		case 5:
			return "Failed in loading playchoice textures";
		case 6:
			return "Failed in loading gallery textures";
		case 7:
			return "Failed in loading playspace textures";
		default:
			return "";
	}
}

void ExitHandler::saveToFile(std::string message) {
	if (!std::filesystem::exists("ErrorLogs"))
		std::filesystem::create_directories("ErrorLogs");
	std::string filePath = "ErrorLogs/ErrorLogs1.txt";
	int i = 1;
	while (std::filesystem::exists(filePath)) {
		i++;
		filePath = "ErrorLogs/ErrorLogs" + std::to_string(i) + ".txt";
	}
	std::ofstream file(filePath);
	if (file.is_open()) {
		file << message << std::endl;
		file.close();
	}
}

void ExitHandler::printOut(std::string message) {
	std::cerr << std::endl << "*******************************" << std::endl;
	std::cerr << message;
	std::cerr << std::endl << "*******************************" << std::endl;
}

void ExitHandler::handleExitCode(int exitCode) {
	if (exitCode != 0) {
		std::string message = getMessage(exitCode);
		saveToFile(message);
		printOut(message);
	}
}