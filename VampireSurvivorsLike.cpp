#include "Engine.h"
#include "ExitHandler.h"

int main()
{
    Engine engine;
    int errorCode = engine.mainLoop();
    ExitHandler exitHandler;
    exitHandler.handleExitCode(errorCode);
    return 0;
}