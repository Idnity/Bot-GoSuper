#pragma once
#include <array>
#include <vector>

#include "SCoord.h"

enum BotTask { Clicking, WaitingOnNewBoard };

class Bot
{
public:
    Bot();
    void tick(float DeltaTime);
    void startupBot(std::vector<SCoord> BestClickSequence);

    // this will also register new mouse pos, so mouse moved is still false
    void ExecuteClick(int x, int y);
    bool HasMovedCursor();
    
    std::array<int, 132> GetScreenBoardFromBounds();
    int GetTypeFromPixel(int row, int col);
    void SetBounds();
    void ClearBounds();
    bool IsBoundsSet();
    int GetColumnToScreenPos(int column);
    int GetRowToScreenPos(int row);
    
    int topLeftBoardX = 0;
    int topLeftBoardY = 0;

    int rightBottomBoardX = 0;
    int rightBottomBoardY = 0;

    int cursorX = 0;
    int cursorY = 0;

    BotTask botTask = Clicking;
    bool RequestingNewBoard = false;
    
private:
    
    std::vector<SCoord> clickSequence;
    int clickIndex;
    float updateTime = 0;
    float currentTime = 0;

    int numRows = 12;
    int numCols = 11;
    
};




