#include "grid.h"
#include <iostream>
#include <raylib.h>

grid::grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    colors = GetCellColors();
    Initialize();
}

void grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            grid2D[row][column] = 0;
        }
    }
}

void grid::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            std::cout << grid2D[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = grid2D[row][column];
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

std::vector<Color> grid::GetCellColors()
{
    Color darkGrey = {26, 31, 40, 255};
    Color green = {47, 230, 23, 255};
    Color red = {232, 18, 18, 255};
    Color orange = {226, 116, 17, 255};
    Color yellow = {237, 234, 4, 255};
    Color purple = {166, 0, 247, 255};
    Color cyan = {21, 204, 209, 255};
    Color blue = {13, 64, 216, 255};

    return{darkGrey, green, red, orange, yellow, purple, cyan, blue};
}
