#include <iostream>
#include <raylib.h>
#include <string>

#include "Application.h"
#include "colors.h"
#include "WindowSettings.h"

enum AppState { SetBounds, Simulating, Executing };

int main()
{
    // Initialize Application
    WindowSettings window_settings{560, 420};
    AppState app_state = SetBounds;
    Application application = Application(&window_settings);
    
    // loading
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    // window setup
    InitWindow(window_settings.width, window_settings.height, "GoSuperFastModel - bot");
    SetTargetFPS(300);
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        // UI
        DrawTextEx(font, "~ Go Turbo Model v1 ~", {20, 13}, 28, 2, WHITE);
        
        DrawRectangleRounded({350, 13, 200, 50}, 0.3f, 6, lightBlue);
        switch (app_state)
        {
        case SetBounds:
            DrawTextEx(font, "Set Bounds", {375, 25}, 26, 2, RED);
            break;
        case Simulating:
            DrawTextEx(font, "Simulating", {385, 25}, 26, 2, WHITE);
            break;
        case Executing:
            DrawTextEx(font, "Executing", {385, 25}, 26, 2, GREEN);
            break;
        }

        //text tutorial keybindings
        DrawRectangleRounded({350, 75, 200, 155}, 0.3f, 6, lightBlue);
        DrawTextEx(font, "Space - toggle auto\n"
                         "1-3 - Sim speed\n"
                         "A - Random board\n"
                         "S - Iterate\n"
                         "D - Bounds (twice)\n"
                         "ESC - CLOSE", {365, 85}, 16, 2, WHITE);
        
        //Stats - Iterations, attempts
        DrawRectangleRounded({350, 245, 200, 155}, 0.3f, 6, lightBlue);
        std::string iterations_string = std::to_string(application.totalIterations);
        DrawTextEx(font, iterations_string.c_str(), {365, 255}, 16, 2, WHITE);

        
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

