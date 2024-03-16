#include <iostream>
#include <raylib.h>
#include <string>

#include "Application.h"
#include "colors.h"
#include "WindowSettings.h"


int main()
{
    // Initialize Application
    WindowSettings window_settings{560, 420};
    Application application = Application(&window_settings);
    
    // loading
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    // window setup
    InitWindow(window_settings.width, window_settings.height, "GoSuperFastModel - bot");
    SetTargetFPS(0);
    
    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        // UI
        DrawTextEx(font, "~ Go Turbo Model v1 ~", {20, 13}, 28, 2, WHITE);
        
        DrawRectangleRounded({350, 13, 200, 50}, 0.6f, 6, lightBlue);
        switch (application.app_state)
        {
        case SetBounds:
            DrawTextEx(font, "Set Bounds", {375, 25}, 26, 2, RED);
            break;
        case Searching:
            DrawTextEx(font, "Searching..", {380, 25}, 26, 2, ORANGE);
            break;
        case Solved:
            DrawTextEx(font, "SOLVED!", {395, 25}, 26, 2, YELLOW);
            break;
        case BotExecuting:
            switch (application.bot.botState)
            {
                case Clicking:
                    if (application.AutomationEnabled)
                    {
                        DrawTextEx(font, "Executing", {385, 25}, 26, 2, GREEN);
                    }
                    else
                    {
                        DrawTextEx(font, "- Paused -", {385, 25}, 26, 2, YELLOW);
                    }
                    break;
                case WaitingOnNewBoard:
                    DrawTextEx(font, "Wait for board..", {365, 27}, 22, 2, YELLOW);
                    break;
            }
        }

        //text tutorial keybindings
        DrawRectangleRounded({350, 75, 200, 155}, 0.05f, 6, lightBlue);
        DrawTextEx(font, "Space - toggle auto\n"
                         "1-3 - Sim speed\n"
                         "A - Random board\n"
                         "S - Next step\n"
                         "D - Bounds (twice)\n"
                         "ESC - CLOSE", {365, 85}, 16, 2, WHITE);
        
        //Stats - Iterations, attempts
        DrawRectangleRounded({350, 238, 200, 80}, 0.1f, 6, lightBlue);
        
        std::string stats_string = "Automation= ";
        stats_string.append(application.AutomationEnabled ? "true" : "false");
        stats_string.append("\nSteps= ");
        stats_string.append(std::to_string(application.totalIterations));
        stats_string.append("\nAttempts= ");
        stats_string.append(std::to_string(application.attempts));
        DrawTextEx(font, stats_string.c_str(), {365, 246}, 16, 2, WHITE);

        // bounds UI
        DrawRectangleRounded({350, 326, 200, 82}, 0.1f, 6, lightBlue);

        std::string bounds_string = "\n------Bounds------";
        if (application.bot.topLeftBoardX == 0 && application.bot.topLeftBoardY == 0)
        {
            bounds_string.append("\nmissing top left");
        }else{
            bounds_string.append("\nX: ");
            bounds_string.append(std::to_string(application.bot.topLeftBoardX));
            bounds_string.append("  Y: ");
            bounds_string.append(std::to_string(application.bot.topLeftBoardY));
        }
        if (application.bot.rightBottomBoardX == 0 && application.bot.rightBottomBoardY == 0)
        {
            bounds_string.append("\nmissing bottom right");
        }else{
            bounds_string.append("\nX: ");
            bounds_string.append(std::to_string(application.bot.rightBottomBoardX));
            bounds_string.append("  Y: ");
            bounds_string.append(std::to_string(application.bot.rightBottomBoardY));
        }
        DrawTextEx(font, bounds_string.c_str(), {365, 310}, 16, 2, WHITE);

        
        application.tick();
        application.Draw();
        EndDrawing();
    }
    CloseWindow();

    // unload
    UnloadFont(font);
    
    return 0;
}