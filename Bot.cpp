#include "Bot.h"

#include <vector>
#include <Windows.h>

Bot::Bot()
{
}

void Bot::tick()
{
}

std::array<int, 132> Bot::GetScreenBoardFromBounds()
{
    std::array<int, 132> result = {};

    // Get the screen DC (Device Context)
    HDC hdcScreen = GetDC(NULL);
    
    std::vector<COLORREF> foundColors = {};
    
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            // Get the color of the pixel at (x, y)
            int x = GetColumnToScreenPos(col);
            int y = GetRowToScreenPos(row);
            COLORREF PixelColor = GetPixel(hdcScreen, x, y);

            float tolerance = 30;

            auto isEqual = [tolerance](float a, float b) {
                return std::abs(a - b) < tolerance;
            };

            bool foundExistingColor = false;

            // find color with small variation acceptance
            for (int i = 0; i < foundColors.size(); ++i)
            {
                if (isEqual(GetRValue(foundColors[i]), GetRValue(PixelColor)) &&
                    isEqual(GetGValue(foundColors[i]), GetGValue(PixelColor)) &&
                    isEqual(GetBValue(foundColors[i]), GetBValue(PixelColor)))
                {
                    result[row * (numRows-1) + col] = i + 1;
                    foundExistingColor = true;
                    break;
                }
            }
            
            // if not found, register new color type and add
            if (!foundExistingColor && foundColors.size() < 7)
            {
                foundColors.push_back(PixelColor);
                result[row * (numRows-1) + col] = foundColors.size();
            }
        }
    }

    // Release the screen DC
    ReleaseDC(NULL, hdcScreen);

    return result;
}

void Bot::SetBounds()
{
    POINT cursorPos;
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

int Bot::GetColumnToScreenPos(int column)
{
    double columnWidth = static_cast<double>(rightBottomBoardX - topLeftBoardX) / static_cast<double>(numCols - 1);
    return static_cast<int>(round(columnWidth * column + topLeftBoardX));
}

int Bot::GetRowToScreenPos(int row)
{
    double rowWidth = static_cast<double>((rightBottomBoardY - topLeftBoardY)) / static_cast<double>((numRows - 1));
    return static_cast<int>(round(rowWidth * row + topLeftBoardY));
}
