#pragma once
#include <array>
#include <vector>

#include "SCoord.h"

class Bot
{
public:
    Bot();
    void tick();
    void startupBot(std::vector<SCoord> BestClickSequence);
    
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
    
private:
    
    std::vector<SCoord> clickSequence;
    int clickIndex;

    int numRows = 12;
    int numCols = 11;
    
};




