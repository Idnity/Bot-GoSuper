#include "Application.h"

#include "Bot.h"

Application::Application()
{
    grid = Grid();
    GenerateRandomBoard();
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
        break;
    case KEY_A:
        GenerateRandomBoard();
        StartAttempt();
        break;
    default: ;
    }
}

void Application::IterateTask()
{
    totalIterations++;
    
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
    grid.ClickSequence.clear();
    grid.SetCurrentGrid(CachedBoard);
}

void Application::GenerateRandomBoard()
{
    for (int i = 0; i < CachedBoard.size(); ++i)
    {
        CachedBoard[i] = 1 + rand() % 4;
    }
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
        foundSolution = true;
        AutomationEnabled = false;
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
