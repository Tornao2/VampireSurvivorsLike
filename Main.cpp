#include "Engine.h"
#include "ExitHandler.h"

int main()
{
    srand((unsigned int) time(0));
    Engine engine;
    engine.mainLoop();
    ExitHandler exitHandler;
    exitHandler.handleExitCode(engine.getErrorCode());
    return 0;
}

//ADD BOSS ENEMIES
//ADD REMOVING ENEMIES WHEN THEY ARE TOO FAR/MOVING BOSS ENEMIES
