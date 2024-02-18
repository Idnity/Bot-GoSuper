#include "grid.h"
#include <iostream>
#include <raylib.h>
#include "colors.h"

using namespace std;

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

bool Grid::PushGridDown()
{
    bool didChange = false;
    for (int row = numRows - 2; row >= 0; row--)
    {
        for (int column = 0; column < numCols; column++)
        {
            if (grid2D[row][column] != 0)
            {
                if (PushItemDown(row, column))
                    didChange = true;
            }
        }
    }
    return didChange;
}

bool Grid::PushGridRight()
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
    return emptyColumns > 0;
}

void Grid::MoveColumnRight(int column, const int numCols)
{
    for (int row = 0; row < numRows; ++row)
    {
        grid2D[row][column + numCols] = grid2D[row][column];
        grid2D[row][column] = 0;
    }
}

bool Grid::PushItemDown(int row, int column)
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
        return true;
    }
    return false;
}

bool Grid::HasCellAdjacentWithSameType(int row, int column)
{
    int typeOfCell = grid2D[row][column];
    
    // check horizontal cells and click if same type
    if(column+1 < numCols && grid2D[row][column+1] == typeOfCell)
        return true;
    if(column-1 >=0 && grid2D[row][column-1] == typeOfCell)
        return true;
    
    // check vertical cells and click if same type
    if(row+1 < numRows && grid2D[row+1][column] == typeOfCell)
        return true;
    if(row-1 >=0 && grid2D[row-1][column] == typeOfCell)
        return true;
    
    return false;
}

void Grid::DoRandomValidClick()
{
    vector<SCoord> testTargets = CoordsWithContent;
    int index = testTargets.size()-1;
    SCoord ClickTarget = testTargets[index];

    while (!HasCellAdjacentWithSameType(ClickTarget.row, ClickTarget.column))
    {
        if (testTargets.size()-1 > 0)
        {
            index = rand()%max(testTargets.size()-1, 0);
        }
        ClickTarget = CoordsWithContent[index];
        testTargets.erase(testTargets.begin() + index);
    }
    ClickCell(ClickTarget.row, ClickTarget.column);
    
    // add to sequence
    ClickSequence.push_back(ClickTarget);
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

gridState Grid::GetGridState()
{
    UpdateCoordsWithContent();
    
    // check if coords with content has adjacent clickable cells of same type
    for (SCoord coords_with_content : CoordsWithContent)
    {
        if (HasCellAdjacentWithSameType(coords_with_content.row, coords_with_content.column))
        {
            return inProgress;
        }
    }
    return CoordsWithContent.empty() ? won : lost;
}

void Grid::UpdateCoordsWithContent()
{
    CoordsWithContent.clear();
    
    // find content
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; ++column)
        {
            if (grid2D[row][column] != 0)
            {
                CoordsWithContent.push_back(SCoord{row, column});
            }
        }
    }
}
