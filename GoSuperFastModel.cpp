#include <iostream>
#include "grid.h"
#include "raylib.h"


int main()
{
    //game settings
    int MaxSolverIterations = 2;

    
    //Application start
    InitWindow(301, 601, "GoSuperBot");
    SetTargetFPS(60);

    grid grid;
    grid.grid2D[0][3] = 1;
    grid.grid2D[2][6] = 2;
    grid.grid2D[4][0] = 6;
    grid.grid2D[0][2] = 2;
    
    grid.Print();
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        grid.Draw();
        
        EndDrawing();
    }
    
    CloseWindow();

    
    std::cout << "Welcome to turbo booster that probably will get your account banned!" << std::endl
    << "Click top left corner -> ";

    
    return 0;
}

