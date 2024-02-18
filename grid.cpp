#include "grid.h"
#include <iostream>
#include <raylib.h>
#include "colors.h"

Grid::Grid()
{
    numRows = 10;
    numCols = 10;
    cellSize = 30;
    colors = GetCellColors();
    Initialize();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            grid2D[row][column] = 0;
        }
    }
}

void Grid::Print()
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

void Grid::Draw()
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

bool Grid::IsCellEmpty(int row, int column)
{
    if (grid2D[row][column] == 0)
    {
        return true;
    }
    return false;
}

bool Grid::IsColumnEmpty(int column)
{
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (grid2D[row][column] != 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::PushGridDown()
{
    for (int row = numRows - 2; row >= 0; row--)
    {
        for (int column = 0; column < numCols; column++)
        {
            if (grid2D[row][column] != 0)
            {
                PushItemDown(row, column);
            }
        }
    }
}

void Grid::PushGridRight()
{
    int emptyColumns = 0;
    for (int column = numCols - 1; column >= 0; column--)
    {
        if (IsColumnEmpty(column))
        {
           emptyColumns++;
        }
        else if (emptyColumns > 0)
        {
            MoveColumnRight(column, emptyColumns);
        }
    }
}

void Grid::MoveColumnRight(int column, const int numCols)
{
    for (int row = 0; row < numRows; ++row)
    {
        grid2D[row][column + numCols] = grid2D[row][column];
        grid2D[row][column] = 0;
    }
}

void Grid::PushItemDown(int row, int column)
{
    int unoccupiedRow = row;
    
    // find the furthest unoccupied spot
    while (IsCellEmpty(unoccupiedRow + 1, column))
    {
        unoccupiedRow++;
    }

    // update item
    if(unoccupiedRow != row)
    {
        grid2D[unoccupiedRow][column] = grid2D[row][column];
        grid2D[row][column] = 0;
    }
}

void Grid::DoRandomValidClick()
{
    // get valid cell click
    int pressRow = rand()%numRows;
    int pressColumn = rand()%numCols;
    while (IsCellEmpty(pressRow, pressColumn))
    {
        pressRow = rand()%numRows;
        pressColumn = rand()%numCols;
    }
    
    ClickCell(pressRow, pressColumn);

    // check game state, reload game and store score of run
}

void Grid::ClickCell(int row, int column)
{
    int typeOfCell = grid2D[row][column];
    if (typeOfCell == 0)
        return;

    // clear cell
    grid2D[row][column] = 0;
    
    // check vertical cells and click if same type
    if(row+1 >=0 && row+1 < numRows && grid2D[row+1][column] == typeOfCell)
        ClickCell(row+1, column);
    if(row-1 >=0 && row-1 < numRows && grid2D[row-1][column] == typeOfCell)
        ClickCell(row-1, column);

    // check horizontal cells and click if same type
    if(column+1 >=0 && column+1 < numCols && grid2D[row][column+1] == typeOfCell)
        ClickCell(row, column+1);
    if(column-1 >=0 && column-1 < numCols && grid2D[row][column-1] == typeOfCell)
        ClickCell(row, column-1);
}

int Grid::GetGameState()
{
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (grid2D[row][column] != 0)
        {
            return false;
        }
    }
    return true;
}