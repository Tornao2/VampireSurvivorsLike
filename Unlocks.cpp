#include "Unlocks.h"

void Unlocks::saveUnlocked(std::vector<bool> boolArray, std::string filename) {
	std::string filePath = std::string("Resources/").append(filename);
	std::ofstream file(filePath);
	for (bool b : boolArray) 
		file << b << '\n';
	file.close();
}

std::vector<bool> Unlocks::loadUnlocked(std::string filename) {
	std::string filePath = std::string("Resources/").append(filename).append(".txt");
	std::ifstream myfile(filePath);
	if (!myfile.is_open()) {
		std::ofstream file(filePath);
		if (filename == "CharactersUnlocked.txt") {
			file << 1 << '\n';
			for (int i = 1; i < NUMBEROFCHARS; i++) 
				file << 0 << '\n';
		}
		else {
			file << 1 << '\n' << 0;
			for (int i = 1; i < NUMBEROFMAPS; i++)
				file << 0 << '\n';
		}
		file.close();
		myfile.open(filePath);
	}
	std::string line;
	std::vector<bool> returnVec;
	while (getline(myfile, line))
		returnVec.push_back(line.compare("1") ? 0 : 1);
	myfile.close();
	return returnVec;
}