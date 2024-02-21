#include <iostream>
#include <raylib.h>
#include "Application.h"

int main()
{
    // Initialize Application
    Application application = Application();

    // window setup
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(400, 600, "GoSuperBot");
    SetTargetFPS(700);
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        application.tick();
        EndDrawing();
    }
    
    CloseWindow();
    
    // std::cout << "Welcome to turbo booster that probably will get your account banned!" << std::endl
    // << "Click top left corner -> ";

    
    return 0;
}

