#include "Engine.h"
#include "ExitHandler.h"

int main()
{
    srand(time(0));
    Engine engine;
    engine.mainLoop();
    ExitHandler exitHandler;
    exitHandler.handleExitCode(engine.getErrorCode());
    return 0;
}