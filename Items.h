#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics/Sprite.hpp>

typedef struct itemInfo {
	int itemId, currentLevel, maxLevel;
	sf::Sprite* sprite;
}itemInfo;

static std::unordered_map<int, std::vector<std::string>> weaponMessages = {
	{0, { "Increase HP\nby 20%", "Increase HP\nby further 20%", "Increase HP\nby further 15%", "Increase base\nHP by 20", "Increase HP\nfurther by 30%"}},
	{1, {"Increase dmg\nby 10%", "Increase dmg\nby further 10%", "Increase dmg\nby further 15%", "Increase base\ndmg by 1", "Increase base\ndmg by 2"}},
	{2, {"Increase ms\nby 5%", "Increase ms\nby further 10%", "Increase ms\nby further 15%", "Increase base\nms by 0.1", "Increase ms\nfurther by 10%"}},
	{3, {"Increase armor\nby 1", "Increase armor\nby further 1", "Increase armor\nby further 1", "Increase armor\nby further 1", "Increase armor\nby further 2"}},
	{4, {"Increase xp\nby 5%", "Increase xp by\nfurther 5%", "Increase xp by\nfurther 10%", "Increase xp\nby further 5%", "Increase xp\nby further 10%"}}
};

std::string getUpgradeText(int itemId, int upgradeToLevel);