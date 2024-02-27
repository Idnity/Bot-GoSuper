#pragma once
#include "Bot.h"
#include "grid.h"
#include "WindowSettings.h"

class Application
{
public:
    Application(WindowSettings *window_settings = nullptr);
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
    WindowSettings* window_settings_;

    // statistics
    int attempts = 0;
    int taskIteration = 0;
    int totalIterations = 0;
    bool AutomationEnabled = false;
    bool foundSolution = false;
    int currentBestScore = 0;
private:

    std::array<int, 132> CachedBoard;
    
};
