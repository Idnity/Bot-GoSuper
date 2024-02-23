#pragma once
#include "Bot.h"
#include "grid.h"

class Application
{
public:
    Application();
    ~Application();
    void Draw();
    void HandleInput();
    void IterateTask();
    void StartAttempt();
    void GenerateRandomBoard();
    void HandleGridState(gridState state);

    void StartupBot();
    void tick();

    Grid grid;
    Bot bot;
    bool isBotRunning = false;

private:
    int taskIteration = 0;

    // statistics
    int attempts = 0;
    int totalIterations = 0;
    bool AutomationEnabled = false;
    bool foundSolution = false;
    int currentBestScore = 0;
    std::array<int, 132> CachedBoard;
    
};
