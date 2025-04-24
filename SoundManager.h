#pragma once
#include <SFML/Audio.hpp>

class SoundManager {
	std::vector<sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound*> soundHolders;
public:
	void loadSounds();
	void playSound(std::string text);
	void setSoundVolume(int volume);
};