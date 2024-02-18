#pragma once
#include "grid.h"

class Application
{
public:
    Application();
    void Draw();
    void HandleInput();
    void IterateTask();
    void StartTrial();
    void FetchGameboard();
    
    Grid grid;

private:
    int taskIteration = 0;
    
};
