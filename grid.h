#pragma once
#include <raylib.h>
#include <vector>

#include "SCoord.h"

enum gridState
{
    inProgress,
    won,
    lost
};

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    
    bool IsCellEmpty(int row, int column);
    bool IsColumnEmpty(int column);

    bool PushGridDown();
    bool PushGridRight();
    void MoveColumnRight(int column, int numCols);
    bool PushItemDown(int row, int column);
    bool HasCellAdjacentWithSameType(int row, int column);

    void DoRandomValidClick();
    void ClickCell(int row, int column);
    gridState GetGridState();
    void UpdateCoordsWithContent();

    std::vector<SCoord> CoordsWithContent;
    std::vector<SCoord> ClickSequence;
    int grid2D[20][10];
    
    int numRows;
    int numCols;
    
private:
    int cellSize;
    std::vector<Color> colors;
};
