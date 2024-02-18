#pragma once
#include "Bot.h"
#include "grid.h"

class Application
{
public:
    Application();
    void Draw();
    void HandleInput();
    void IterateTask();
    void StartAttempt();
    void FetchGameboard();
    void HandleGridState(gridState state);

    void StartupBot();
    void tick();

    Grid grid;
    Bot bot;
    bool isBotRunning = false;
    bool AutomationEnabled = false;
    int attempts = 0;

private:
    int taskIteration = 0;
    
};
