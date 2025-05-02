#include "Items.h"

std::string getUpgradeText(int itemId, int upgradeToLevel) {
	return weaponMessages[itemId - 1][upgradeToLevel - 1];
}
