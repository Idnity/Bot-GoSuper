#pragma once
#include <array>
#include <raylib.h>
#include <vector>

#include "SCoord.h"
#include "WindowSettings.h"

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
    void SetCurrentGrid(std::array<int, 132> array);
    void Print();
    void Draw();
    
    bool IsCellEmpty(int row, int column);
    bool IsColumnEmpty(int column);

    bool PushGridDown();
    bool PushGridRight();
    void MoveColumnRight(int column, int numCols);
    bool PushItemDown(int row, int column);
    bool HasCellAdjacentWithSameType(int row, int column);

    void ClickCell(int row, int column);
    gridState GetGridState();
    void UpdateCoordsWithContent();

    std::vector<SCoord> CoordsWithContent;
    std::vector<SCoord> ClickableCells;

    // standard game uses 12 rows and 11 columns
    std::array<int, 132> gridV2;
    int GetGridElement(int row, int column);
    int GetGridV2Index(int row, int column);
    bool CellIsValid(int row, int column);
    
    int numRows = 12;
    int numCols = 11;
    
private:
    int cellSize = 30;
    std::vector<Color> colors;
};
