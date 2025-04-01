#include "Unlocks.h"

void Unlocks::saveUnlocked(std::vector<bool> boolArray, std::string filename) {
	std::string filePath = std::string("Resources/").append(filename);
	std::ofstream file(filePath);
	for (bool b : boolArray) {
		file << b << '\n';
	}
	file.close();
}

std::vector<bool> Unlocks::loadUnlocked(std::string filename) {
	std::string filePath = std::string("Resources/").append(filename);
	std::ifstream myfile(filePath);
	if (!myfile.is_open()) return std::vector<bool>();
	std::string line;
	std::vector<bool> returnVec;
	while (getline(myfile, line))
	{
		returnVec.push_back(line.compare("1") ? 0 : 1);
	}
	myfile.close();
	return returnVec;
}