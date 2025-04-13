#pragma once
#include <vector>
#include <fstream>
#include <sstream>

struct ModifierNode {
	std::string name = "";
	int currentLevel = 0, maxLevel =0;
	float effectStrength =0;
};

class Modifiers {
	std::vector <ModifierNode> modVector;
	int coins = 0;
	void loadCleanModifiers();
public:
	void loadModifiersFromFile();
	void saveModifiersToFile();
	ModifierNode* getNodeByName(std::string readName);
	std::vector<ModifierNode>* getVector();
	std::string getModStrength(int readIndex);
	std::string getModLevel(int readIndex);
	std::string getCoins();
	unsigned char* getColumnAmounts();
	unsigned char getRowAmount();
	void increaseLevel(int index);
	void changeCoins(int readCoinChange);
};