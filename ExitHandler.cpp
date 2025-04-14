#include "ExitHandler.h"

std::string ExitHandler::getMessage(int readExitCode) {
	switch (readExitCode) {
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
			return "Failed in loading playspace textures";
		case 7:
			return "Failed in loading finishscene textures";
		default:
			return "Unkown error";
	}
}

void ExitHandler::saveToFile(std::string readMessage) {
	if (!std::filesystem::exists("ErrorLogs"))
		std::filesystem::create_directories("ErrorLogs");
	std::string filePath = "ErrorLogs/ErrorLogs1.txt";
	int fileNum = 1;
	while (std::filesystem::exists(filePath)) {
		fileNum++;
		filePath = "ErrorLogs/ErrorLogs" + std::to_string(fileNum) + ".txt";
	}
	std::ofstream file(filePath);
	if (file.is_open()) {
		file << readMessage << std::endl;
		file.close();
	}
}

void ExitHandler::printToConsole(std::string readMessage) {
	std::cerr << std::endl << "*******************************" << std::endl;
	std::cerr << readMessage;
	std::cerr << std::endl << "*******************************" << std::endl;
}

void ExitHandler::handleExitCode(int readExitCode) {
	if (readExitCode != 0) {
		std::string message = getMessage(readExitCode);
		saveToFile(message);
		printToConsole(message);
	}
}