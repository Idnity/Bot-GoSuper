#include <iostream>
#include <raylib.h>
#include "Application.h"

int main()
{
    // Initialize Application
    Application application = Application();

    // loading
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    // window setup
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(530, 380, "GoSuperBot");
    SetTargetFPS(700);
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        // UI
        DrawTextEx(font, "Iterations", {365, 15}, 28, 2, WHITE);
        
        application.tick();
        EndDrawing();
    }
    CloseWindow();

    // unload
    //UnloadFont(font);
    
    // std::cout << "Welcome to turbo booster that probably will get your account banned!" << std::endl
    // << "Click top left corner -> ";

    
    return 0;
}

