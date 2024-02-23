#include "Bot.h"
#include <Windows.h>

Bot::Bot()
{
}

void Bot::tick()
{
}

void Bot::FetchScreenBoardToArray(std::array<int, 132> array)
{
    // Get the screen DC (Device Context)
    HDC hdcScreen = GetDC(NULL);

    // Define the screen coordinates of the pixel you want to get the color of
    int x = 100; // x-coordinate
    int y = 50;  // y-coordinate

    // Get the color of the pixel at (x, y)
    COLORREF color = GetPixel(hdcScreen, x, y);

    // Release the screen DC
    ReleaseDC(NULL, hdcScreen);

    // Extract the RGB components from the COLORREF value
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

}
