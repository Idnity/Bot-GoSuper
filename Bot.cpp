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
            COLORREF foundColor = GetPixel(hdcScreen, x, y);
            
            auto it = std::find(foundColors.begin(), foundColors.end(), foundColor);
            if (it != foundColors.end())
            {
                int index = it - foundColors.begin();
                result[row * (numRows-1) + col] = index + 1;
            }
            else if (foundColors.size() < 7)
            {
                foundColors.push_back(foundColor);
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
    int columnWidth = (rightBottomBoardX - topLeftBoardX) / numCols;
    return columnWidth * column + topLeftBoardX;
}

int Bot::GetRowToScreenPos(int row)
{
    int rowWidth = (rightBottomBoardY - topLeftBoardY) / numRows;
    return rowWidth * row + topLeftBoardY;
}
