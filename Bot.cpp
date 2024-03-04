#include "Bot.h"

#include <vector>
#include <Windows.h>

Bot::Bot()
{
}

void Bot::tick(float DeltaTime)
{
    // check if time to update
    currentTime += DeltaTime;
    if (currentTime >= updateTime)
    {
        currentTime = 0;

        switch (botTask)
        {
        case Clicking:
            if (clickIndex < clickSequence.size())
            {
                ExecuteClick(GetColumnToScreenPos(clickSequence[clickIndex].column), GetRowToScreenPos(clickSequence[clickIndex].row));
                clickIndex++;
            }
            else
            {
                updateTime = 2;
                botTask = WaitingOnNewBoard;
            }
            break;
            
        case WaitingOnNewBoard:
            RequestingNewBoard = true;
            break;
        }
    }
}

void Bot::startupBot(std::vector<SCoord> BestClickSequence)
{
    clickSequence = BestClickSequence;
    clickIndex = 0;
    currentTime = 0;
    botTask = Clicking;
    RequestingNewBoard = false;
    // click update time between 1 and 1.25
    updateTime = static_cast<float>(rand() / (RAND_MAX * 4) + 0.75);

    POINT cursorPos;
    GetCursorPos(&cursorPos);
    cursorX = cursorPos.x;
    cursorY = cursorPos.y;
}

void Bot::ExecuteClick(int x, int y)
{
    cursorX = x;
    cursorY = y;
    
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // Press left mouse button
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);   // Release left mouse button
}

bool Bot::HasMovedCursor()
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    return !(cursorX == cursorPos.x &&
             cursorY == cursorPos.y);
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

            float tolerance = 35;

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
