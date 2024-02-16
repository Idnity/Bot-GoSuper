#pragma once
#include "grid.h"

class Application
{
public:
    Application();
    void Draw();
    void HandleInput();
    void IterateTask();
    
    Grid grid;

private:
    int taskIteration = 0;
    
};
