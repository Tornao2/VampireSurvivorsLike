#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define NUMBEROFMAPS 3
#define NUMBEROFCHARS 4

class Unlocks {
public:
	void saveUnlocked(std::vector<bool> boolArray, std::string filename);
	std::vector<bool> loadUnlocked(std::string filename);
};