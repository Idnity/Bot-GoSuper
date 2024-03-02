#include "Bot.h"

namespace WinAPI
{
#include <Windows.h>
}

Bot::Bot()
{
}

void Bot::tick()
{
}

std::array<int, 132> Bot::GetScreenBoardFromBounds()
{
    std::array<int, 132> result = {};


    return result;
}

int Bot::GetTypeFromPixel(SCoord coord)
{
    // Get the screen DC (Device Context)
    WinAPI::HDC hdcScreen = WinAPI::GetDC(NULL);

    // Define the screen coordinates of the pixel you want to get the color of
    int x = 100; // x-coordinate
    int y = 50;  // y-coordinate

    // Get the color of the pixel at (x, y)
    WinAPI::COLORREF color = GetPixel(hdcScreen, x, y);

    // Release the screen DC
    ReleaseDC(NULL, hdcScreen);
    
    return 0;
}

void Bot::SetBounds()
{
    WinAPI::POINT cursorPos;
    GetCursorPos(&cursorPos);
    if (topLeftBoardX == 0 && topLeftBoardY == 0)
    {
        topLeftBoardX = cursorPos.x;
        topLeftBoardY = cursorPos.y;
    }
    else
    {
        rightBottomBoardX = cursorPos.x;
        rightBottomBoardY = cursorPos.y;
    }
    
}

void Bot::ClearBounds()
{
    topLeftBoardX = 0;
    topLeftBoardY = 0;
    rightBottomBoardX = 0;
    rightBottomBoardY = 0;
}


bool Bot::IsBoundsSet()
{
    return
    topLeftBoardX != 0 &&
    topLeftBoardY != 0 &&
    rightBottomBoardX != 0 &&
    rightBottomBoardY != 0;
}
