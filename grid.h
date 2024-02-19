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
    void CacheCurrentGameboard();
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
    std::vector<SCoord> ClickableCells;
    std::vector<SCoord> ClickSequence;

    // standard game uses 12 rows and 11 columns
    int grid2D[11][10];
    int cachedGameboard[11][10];
    
    int numRows;
    int numCols;
    
private:
    int cellSize;
    std::vector<Color> colors;
};
