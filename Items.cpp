#include "Items.h"

std::string getUpgradeText(int itemId, int upgradeToLevel) {
	return itemMessages[itemId - 1][upgradeToLevel - 1];
}
