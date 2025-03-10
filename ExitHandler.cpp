#include "ExitHandler.h"

void ExitHandler::handleExitCode(int exitCode) {
	switch (exitCode) {
	case -1:
		std::cerr << "Failed in loading mainmenu textures";
		break;
	}
}