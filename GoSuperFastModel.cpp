#include <iostream>
#include <raylib.h>
#include "Application.h"

// 1.08.00

int main()
{
    // game settings
    int MaxSolverIterations = 2;

    
    // Initialize Application
    Application application = Application();

    // window setup
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(301, 601, "GoSuperBot");
    SetTargetFPS(60);
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        application.HandleInput();
        application.Draw();
        EndDrawing();
    }
    
    CloseWindow();

    
    std::cout << "Welcome to turbo booster that probably will get your account banned!" << std::endl
    << "Click top left corner -> ";

    
    return 0;
}

