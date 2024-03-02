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
        DrawRectangleRounded({350, 75, 200, 165}, 0.3f, 6, lightBlue);
        DrawTextEx(font, "Space - toggle auto\n"
                         "1-3 - Sim speed\n"
                         "A - Random board\n"
                         "S - Iterate\n"
                         "D - Bounds (twice)\n"
                         "ESC - CLOSE", {365, 90}, 16, 2, WHITE);
        
        //Stats - Iterations, attempts
        DrawRectangleRounded({350, 250, 200, 155}, 0.3f, 6, lightBlue);
        
        std::string stats_string = "Iterations= ";
        stats_string.append(std::to_string(application.totalIterations));
        stats_string.append("\nAttempts= ");
        stats_string.append(std::to_string(application.attempts));
        stats_string.append("\nLowestSolution= ");
        stats_string.append(std::to_string(application.bestScore));
        stats_string.append("\nAutomation= ");
        stats_string.append(application.AutomationEnabled ? "true" : "false");
        stats_string.append("\nBounds= ");
        stats_string.append(std::to_string(application.bot.topLeftBoardX));
        stats_string.append(".");
        stats_string.append(std::to_string(application.bot.topLeftBoardY));
        stats_string.append("\n");
        stats_string.append(std::to_string(application.bot.rightBottomBoardX));
        stats_string.append(".");
        stats_string.append(std::to_string(application.bot.rightBottomBoardY));
        
        DrawTextEx(font, stats_string.c_str(), {365, 265}, 16, 2, WHITE);

        
        application.tick();
        application.Draw();
        EndDrawing();
    }
    CloseWindow();

    // unload
    UnloadFont(font);
    
    return 0;
}