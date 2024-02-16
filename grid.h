#pragma once
#include <raylib.h>
#include <vector>

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    
    bool IsCellEmpty(int row, int column);
    bool IsColumnEmpty(int column);
    
    void PushGridDown();
    void PushGridRight();
    void MoveColumnRight(int column, int numCols);
    void PushItemDown(int row, int column);

    void ClickCell(int row, int column);
    
    int grid2D[20][10];
    
private:
    int numRows;
    int numCols;
    int cellSize;
    
    std::vector<Color> colors;
};
