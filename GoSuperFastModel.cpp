#include <iostream>
#include <raylib.h>
#include "Application.h"
#include "colors.h"

int main()
{
    // Initialize Application
    Application application = Application();

    // loading
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    // window setup
    InitWindow(530, 380, "GoSuperFastModel - bot");
    SetTargetFPS(700);
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        // UI
        //text tutorial for shortcuts space, a, s
        //presentable name
        DrawTextEx(font, "Stats - Iterations, attempts", {365, 15}, 28, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3f, 6, lightBlue);
        
        application.tick();
        EndDrawing();
    }
    CloseWindow();

    // unload
    UnloadFont(font);
    
    // std::cout << "Welcome to turbo booster that probably will get your account banned!" << std::endl
    // << "Click top left corner -> ";

    
    return 0;
}

