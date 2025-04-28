#include "SoundManager.h"

void SoundManager::loadSounds(){
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Death.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Menublock.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Menuchange.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Menuselect.wav"));
	soundHolders["death"] = new sf::Sound(soundBuffers[soundBuffers.size() - 4]);
	soundHolders["menuBlock"] = new sf::Sound(soundBuffers[soundBuffers.size() - 3]);
	soundHolders["menuChange"] = new sf::Sound(soundBuffers[soundBuffers.size() - 2]);
	soundHolders["menuSelect"] = new sf::Sound(soundBuffers[soundBuffers.size() - 1]);
}

void SoundManager::playSound(std::string text, bool checkBreak) {
	if (soundHolders.find(text) != soundHolders.end()) {
		sf::Time time = soundHolders.at(text)->getPlayingOffset();
		if (!checkBreak)
			soundHolders.at(text)->play();
		else if (time.asMilliseconds() > 50 || time.asMilliseconds() == 0)
			soundHolders.at(text)->play();
	}
}

void SoundManager::setSoundVolume(int volume){
	for (auto [key, value] : soundHolders) 
		value->setVolume(volume);
}