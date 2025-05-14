#include "Modifiers.h"

void Modifiers::loadCleanModifiers() {
	coins = 0;
	modVector.push_back({ "Health%", 0, 5, (float) 0.2 });
	modVector.push_back({ "Damage%", 0, 5, (float)0.1 });
	modVector.push_back({ "Move%", 0, 5, (float) 0.05 });
	modVector.push_back({ "Exp%", 0, 4, (float) 0.05 });
	modVector.push_back({ "Armor", 0, 4, 1 });
}

void Modifiers::loadModifiersFromFile() {
	std::ifstream inFile("Resources/Upgrade.txt");
	if (!inFile) 
		loadCleanModifiers();
	else {
		std::string line;
		std::getline(inFile, line);
		coins = std::stoi(line);
		while (std::getline(inFile, line)) {
			std::stringstream ss(line);
			ModifierNode mod;
			std::string subString;
			std::getline(ss, mod.name, ';');
			std::getline(ss, subString, ';');
			mod.currentLevel = static_cast <unsigned char>(std::stoi(subString));
			std::getline(ss, subString, ';');
			mod.maxLevel = static_cast <unsigned char>(std::stoi(subString));
			std::getline(ss, subString, ';');
			mod.effectStrength = std::stof(subString);
			modVector.push_back(mod);
		}
	}
}

void Modifiers::saveModifiersToFile() {
	std::ofstream outFile("Resources/Upgrade.txt");
	outFile << coins << "\n";
	for (ModifierNode mod : modVector) 
		outFile << mod.name << ";" << mod.currentLevel << ";" << mod.maxLevel << ";" << mod.effectStrength << "\n";
	outFile.close();
}

ModifierNode* Modifiers::getNodeByName(std::string readName) {
	for (int i = 0; i < modVector.size(); i++) {
		if (!modVector[i].name.compare(readName))
			return &modVector[i];
	}
	return nullptr;
}

std::vector<ModifierNode>* Modifiers::getVector() {
	return &modVector;
}

std::string Modifiers::getModStrength(int readIndex) {
	std::string ret = std::to_string(modVector.at(readIndex).effectStrength);
	if (readIndex != 4) {
		ret = std::to_string((int)(std::stof(ret) * 100));
		ret.append("%");
	}
	else 
		ret = std::to_string((int)(std::stof(ret)));
	return ret;
}

std::string Modifiers::getModLevel(int readIndex) {
	return std::to_string(modVector.at(readIndex).currentLevel).append("/").append(std::to_string(modVector.at(readIndex).maxLevel));
}

std::string Modifiers::getCoins() {
	return ((std::string)"Coins: ").append(std::to_string(coins));
}

unsigned char* Modifiers::getColumnAmounts() {
	unsigned char* returnArray = new unsigned char[3];
	int i = (int) modVector.size();
	if (i != 0) {
		for (int j = 0; j < 3 && i > 0; j++) {
			returnArray[j] = i >= 5?5:i;
			i -= 5;
		}
	}
	return returnArray;
}

unsigned char Modifiers::getRowAmount() {
	if (modVector.size() == 0) 
		return 0;
	else 
		return (unsigned char) (modVector.size() -1) / 5 + 1;
}

bool Modifiers::increaseLevel(int index) {
	if (modVector.at(index).maxLevel > modVector.at(index).currentLevel && coins > 100 + std::stoi(getModLevel(index)) * 100) {
		coins -= std::stoi(getModLevel(index)) * 100 + 100;
		modVector.at(index).currentLevel++;
		return true;
	}
	else 
		return false;
}

void Modifiers::changeCoins(int readCoinChange) {
	coins += readCoinChange;
}