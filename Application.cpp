#include "Application.h"

#include "Bot.h"

Application::Application()
{
    grid = Grid();
    StartAttempt();
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
        AutomationEnabled = !AutomationEnabled;
        break;
    case KEY_S:
        IterateTask();
    default: ;
    }
}

void Application::IterateTask()
{
    taskIteration++;
    
    switch (taskIteration)
    {
    case 1:
        if (!grid.PushGridDown())
            IterateTask();
        break;
    case 2:
        if (!grid.PushGridRight())
            IterateTask();
        break;
    case 3:
        // could use check grid to optimize next click if in progress
        HandleGridState(grid.GetGridState());
        break;
    case 4:
        grid.DoRandomValidClick();
        break;
    default:
        taskIteration = 0;
        IterateTask();
    }
}

void Application::StartAttempt()
{
    attempts++;
    taskIteration = 0;
    srand(attempts);
    grid.Initialize();
    grid.ClickSequence.clear();
    FetchGameboard();
}

void Application::FetchGameboard()
{
    for (int row = 0; row < grid.numRows; row++)
    {
        for (int column = 0; column < grid.numCols; column++)
        {
            grid.grid2D[row][column] = 1 + rand() % 4;
        }
    }
    
    grid.UpdateCoordsWithContent();
}

void Application::HandleGridState(gridState state)
{
    switch (state)
    {
    case inProgress:
        IterateTask();
        break;
    case lost:
        // store score if best
        StartAttempt();
        break;
    case won:
        StartAttempt();
        //StartupBot();
        break;
    }
}

void Application::StartupBot()
{
    isBotRunning = true;
}

void Application::tick()
{
    HandleInput();
    if (isBotRunning)
        bot.tick();
    if (AutomationEnabled)
    {
        IterateTask();
    }
    
    Draw();
}
