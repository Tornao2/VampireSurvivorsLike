#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

constexpr int NUMBEROFMAPS = 2;
constexpr int NUMBEROFCHARS = 2;

class Unlocks {
public:
	void saveUnlocked(std::vector<bool> boolArray, std::string filename);
	std::vector<bool> loadUnlocked(std::string filename);
};