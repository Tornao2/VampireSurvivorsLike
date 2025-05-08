#include "SoundManager.h"

void SoundManager::loadSounds(){
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon10.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon9.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon7.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon6.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon5.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon4.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon3.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon2.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/weapon1.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/powerUpChest.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/powerUpBomb.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/powerUpCoin.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/powerUpXp.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/powerUpHp.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Death.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Menublock.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Menuchange.wav"));
	soundBuffers.push_back(sf::SoundBuffer("Resources/Sounds/Menuselect.wav"));
	soundHolders["weapon10"] = new sf::Sound(soundBuffers[soundBuffers.size() - 18]);
	soundHolders["weapon9"] = new sf::Sound(soundBuffers[soundBuffers.size() - 17]);
	soundHolders["weapon7"] = new sf::Sound(soundBuffers[soundBuffers.size() - 16]);
	soundHolders["weapon6"] = new sf::Sound(soundBuffers[soundBuffers.size() - 15]);
	soundHolders["weapon5"] = new sf::Sound(soundBuffers[soundBuffers.size() - 14]);
	soundHolders["weapon4"] = new sf::Sound(soundBuffers[soundBuffers.size() - 13]);
	soundHolders["weapon3"] = new sf::Sound(soundBuffers[soundBuffers.size() - 12]);
	soundHolders["weapon2"] = new sf::Sound(soundBuffers[soundBuffers.size() - 11]);
	soundHolders["weapon1"] = new sf::Sound(soundBuffers[soundBuffers.size() - 10]);
	soundHolders["powerChest"] = new sf::Sound(soundBuffers[soundBuffers.size() - 9]);
	soundHolders["powerBomb"] = new sf::Sound(soundBuffers[soundBuffers.size() - 8]);
	soundHolders["powerCoin"] = new sf::Sound(soundBuffers[soundBuffers.size() - 7]);
	soundHolders["powerXp"] = new sf::Sound(soundBuffers[soundBuffers.size() - 6]);
	soundHolders["powerHp"] = new sf::Sound(soundBuffers[soundBuffers.size() - 5]);
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