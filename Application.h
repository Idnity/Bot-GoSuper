#pragma once
#include "Bot.h"
#include "grid.h"
#include "WindowSettings.h"

enum AppState { SetBounds, Searching, Solved, Executing, Paused };

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
    void DoRandomValidClick();

    void tick();

    Grid grid;
    Bot bot;
    WindowSettings* window_settings_;
    AppState app_state;

    // statistics
    int attempts = 0;
    int taskIteration = 0;
    int totalIterations = 0;
    bool AutomationEnabled = false;
    int bestScore = -1;
    std::vector<SCoord> currentClickSequence;
    std::vector<SCoord> bestClickSequence;
private:

    std::array<int, 132> CachedBoard;
    
};
