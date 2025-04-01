#include "ExitHandler.h"

std::string ExitHandler::getMessage(int exitCode) {
	std::string returnMessage;
	switch (exitCode) {
	case -1:
		returnMessage = "Failed in loading font";
		break;
	case 1:
		returnMessage = "Failed in loading mainmenu textures";
		break;
	case 2:
		returnMessage = "Failed in loading settings textures";
		break;
	case 3:
		returnMessage = "Failed in loading resetchoice textures";
		break;
	case 4:
		returnMessage = "Failed in loading upgrade textures";
		break;
	case 5:
		returnMessage = "Failed in loading playchoice textures";
		break;
	case 6:
		returnMessage = "Failed in loading gallery textures";
		break;
	case 7:
		returnMessage = "Failed in loading playspace textures";
		break;
	}
	return returnMessage;
}

void ExitHandler::saveToFile(std::string message) {
	std::string folderPath = "ErrorLogs";
	if (!std::filesystem::exists(folderPath)) {
		std::filesystem::create_directories(folderPath);
		if (!std::filesystem::exists(folderPath)) {
			return;
		}
	}
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