#include "Application.h"

#include <iostream>

//#include "Bot.h"

Application::Application(WindowSettings *window_settings) : window_settings_(window_settings)
{
    // audio setup
    InitAudioDevice();
    //sound = LoadSound("Sounds/rotate.mp3");
    //PlaySound(sound);
    
    grid = Grid();
    GenerateRandomBoard();
    StartAttempt();
}

Application::~Application()
{
    //UnloadSound(sound);
    CloseAudioDevice();
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
    case KEY_D:
        grid.SetCurrentGrid(std::array<int, 132>{});
        if (bot.IsBoundsSet())
        {
            bot.ClearBounds();
        }
        else
        {
            bot.SetBounds();
        }
        break;
    case KEY_ONE:
        SetTargetFPS(10);
        break;
    case KEY_TWO:
        SetTargetFPS(200);
        break;
    case KEY_THREE:
        SetTargetFPS(0);
        break;
    default: ;
    }
}

void Application::IterateTask()
{
    // if solution found, restart
    if (foundSolution)
    {
        foundSolution = false;
        bestScore = -1;
        GenerateRandomBoard();
        StartAttempt();
        return;
    }
    
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
        DoRandomValidClick();
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
    currentClickSequence.clear();
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
        if (grid.CoordsWithContent.size() < bestScore || bestScore < 0)
        {
            bestClickSequence = currentClickSequence;
            bestScore = grid.CoordsWithContent.size();
        }
        StartAttempt();
        break;
    case won:
        bestClickSequence = currentClickSequence;
        bestScore = grid.CoordsWithContent.size();
        foundSolution = true;
        AutomationEnabled = false;
        //StartupBot();
        break;
    }
}

void Application::DoRandomValidClick()
{
    // can be a valid click?
    if (grid.ClickableCells.empty())
        return;
    
    SCoord ClickTarget = grid.ClickableCells[rand() % grid.ClickableCells.size()];
    grid.ClickCell(ClickTarget.row, ClickTarget.column);
    
    // add to sequence
    currentClickSequence.push_back(ClickTarget);
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
}
