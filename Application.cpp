#include "Application.h"

#include <iostream>


Application::Application(WindowSettings *window_settings) : window_settings_(window_settings)
{
    app_state = SetBounds;
    // audio setup
    InitAudioDevice();
    //sound = LoadSound("Sounds/rotate.mp3");
    //PlaySound(sound);
    
    grid = Grid();
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
            app_state = SetBounds;
        }
        else
        {
            bot.SetBounds();
            if (bot.IsBoundsSet())
            {
                bot.updateTime = 2;
                bot.botState = WaitingOnNewBoard;
                app_state = BotExecuting;
            }
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
    switch (app_state)
    {
    case Solved:
        // if solution found, restart
        if (bot.IsBoundsSet())
        {
            app_state = BotExecuting;
            bot.startupBot(bestClickSequence);
        }
        return;
    }
    
    
    totalIterations++;
    taskIteration++;
    switch (taskIteration)
    {
    case 1:
        grid.PushGridDown();
        grid.PushGridRight();
        break;
    case 2:
        // could use check grid to optimize next click if in progress
        HandleGridState(grid.GetGridState());
        break;
    case 3:
        DoRandomValidClick();
        break;
    default:
        taskIteration = 0;
        IterateTask();
    }
}

void Application::StartAttempt()
{
    app_state = Searching;
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
        app_state = Solved;
        bestClickSequence = currentClickSequence;
        bestScore = grid.CoordsWithContent.size();
        break;
    }
}

void Application::GetBoardFromScreenAndAttempt()
{
    // find board from screen, and start search for solution
    grid.SetCurrentGrid(bot.GetScreenBoardFromBounds());
    CachedBoard = grid.gridV2;
    StartAttempt();
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

void Application::tick()
{
    HandleInput();

    switch (app_state)
    {
    case Searching:
        // auto iterate of automation enabled
        if (AutomationEnabled)
            IterateTask();
        break;

    case Solved:
        // this iteration should start bot execution
        if (AutomationEnabled)
            IterateTask();
        break;
        
    case BotExecuting:
        bot.isRunning = AutomationEnabled;
        bot.tick(GetFrameTime());
        
        if (bot.botState == WaitingForSolution)
        {
            GetBoardFromScreenAndAttempt();
        }
        break;
    }
}
