#include "Application.h"

Application::Application()
{
    grid = Grid();
    FetchGameboard();
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
    case 2:
        grid.DoRandomValidClick();
    break;
        
    default: ;
    }
    if (taskIteration >= 2)
    {
        taskIteration = 0;
    }
    else
    {
        taskIteration++;
    }
}

void Application::StartTrial()
{
    srand(1);
}

void Application::FetchGameboard()
{
    grid.grid2D[9][3] = 1;
    grid.grid2D[2][6] = 2;
    grid.grid2D[4][0] = 6;
    grid.grid2D[6][0] = 4;
    grid.grid2D[5][4] = 2;
    grid.grid2D[8][6] = 2;
    grid.grid2D[5][9] = 2;
    grid.grid2D[1][1] = 2;
}
