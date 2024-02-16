#include "Application.h"

Application::Application()
{
    grid = Grid();
    grid.grid2D[9][3] = 1;
    grid.grid2D[2][6] = 2;
    grid.grid2D[4][0] = 6;
    grid.grid2D[6][0] = 4;
    grid.grid2D[7][2] = 2;
}

void Application::Draw()
{
    grid.Draw();
}

void Application::HandleInput()
{
    switch (GetKeyPressed())
    {
    case KEY_SPACE:
        IterateTask();
        break;
    default: ;
    }
}

void Application::IterateTask()
{
    switch (taskIteration)
    {
    case 0:
        grid.PushGridDown();
        break;
    case 1:
        grid.PushGridRight();
        break;
    case 3:

        grid.ClickCell();
    break;
        
    default: ;
    }
    taskIteration = taskIteration+1%2;
}
