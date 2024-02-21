#include "grid.h"
#include <iostream>
#include <raylib.h>
#include "colors.h"

using namespace std;

Grid::Grid()
{
    colors = GetCellColors();
    gridV2.fill(0);
}

void Grid::SetCurrentGrid(std::array<int, 132> array)
{
    gridV2 = array;
    UpdateCoordsWithContent();
}

void Grid::Print()
{
    for (int i = 0; i < gridV2.size(); ++i)
    {
        std::cout << gridV2[i] << " ";
        if (i%numRows == numRows-1)
            std::cout << '\n';
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = GetGridElement(row, column);
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (GetGridElement(row, column) == 0)
    {
        return true;
    }
    return false;
}

bool Grid::IsColumnEmpty(int column)
{
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (GetGridElement(row, column) != 0)
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
            if (GetGridElement(row, column) != 0)
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
    bool hasMovedColumn = false;
    for (int column = numCols - 1; column >= 0; column--)
    {
        if (IsColumnEmpty(column))
        {
            emptyColumns++;
        }
        else if (emptyColumns > 0)
        {
            MoveColumnRight(column, emptyColumns);
            hasMovedColumn = true;
        }
    }
    return hasMovedColumn;
}

void Grid::MoveColumnRight(int column, const int numCols)
{
    for (int row = 0; row < numRows; ++row)
    {
        gridV2[GetGridV2Index(row, column + numCols)] = GetGridElement(row, column);
        gridV2[GetGridV2Index(row, column)] = 0;
    }
}

bool Grid::PushItemDown(int row, int column)
{
    int unoccupiedRow = row;
    
    // find the furthest unoccupied spot
    while (CellIsValid(unoccupiedRow + 1, column) && IsCellEmpty(unoccupiedRow + 1, column))
    {
        unoccupiedRow++;
    }

    // update item
    if(unoccupiedRow != row)
    {
        gridV2[GetGridV2Index(unoccupiedRow, column)] = GetGridElement(row, column);
        gridV2[GetGridV2Index(row, column)] = 0;
        return true;
    }
    return false;
}

bool Grid::HasCellAdjacentWithSameType(int row, int column)
{
    int typeOfCell = GetGridElement(row, column);
    
    // check horizontal cells and click if same type
    if(column+1 < numCols && GetGridElement(row, column + 1) == typeOfCell)
        return true;
    if(column-1 >= 0 && GetGridElement(row, column - 1) == typeOfCell)
        return true;
    
    // check vertical cells and click if same type
    if(row+1 < numRows && GetGridElement(row + 1, column) == typeOfCell)
        return true;
    if(row-1 >= 0 && GetGridElement(row - 1, column) == typeOfCell)
        return true;
    
    return false;
}

void Grid::DoRandomValidClick()
{
    // can be a valid click?
    if (ClickableCells.empty())
        return;
    
    SCoord ClickTarget = ClickableCells[rand() % ClickableCells.size()];
    ClickCell(ClickTarget.row, ClickTarget.column);
    
    // add to sequence
    ClickSequence.push_back(ClickTarget);
}

void Grid::ClickCell(int row, int column)
{
    int typeOfCell = GetGridElement(row, column);
    if (typeOfCell == 0)
        return;

    // clear cell
    gridV2[GetGridV2Index(row, column)] = 0;
    
    // check vertical cells and click if same type
    if(row+1 >=0 && row+1 < numRows && GetGridElement(row + 1, column) == typeOfCell)
        ClickCell(row+1, column);
    if(row-1 >=0 && row-1 < numRows && GetGridElement(row - 1, column) == typeOfCell)
        ClickCell(row-1, column);

    // check horizontal cells and click if same type
    if(column+1 >=0 && column+1 < numCols && GetGridElement(row, column + 1) == typeOfCell)
        ClickCell(row, column+1);
    if(column-1 >=0 && column-1 < numCols && GetGridElement(row, column - 1) == typeOfCell)
        ClickCell(row, column-1);
}

gridState Grid::GetGridState()
{
    UpdateCoordsWithContent();
    ClickableCells.clear();
    
    // check if coords with content has adjacent clickable cells of same type
    for (SCoord coords_with_content : CoordsWithContent)
    {
        if (HasCellAdjacentWithSameType(coords_with_content.row, coords_with_content.column))
        {
            ClickableCells.push_back(coords_with_content);
        }
    }
    if(!ClickableCells.empty())
        return inProgress;
    
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
            if (GetGridElement(row, column) != 0)
            {
                CoordsWithContent.push_back(SCoord{row, column});
            }
        }
    }
}

int Grid::GetGridElement(int row, int column)
{
    return gridV2[GetGridV2Index(row, column)];
}

int Grid::GetGridV2Index(int row, int column)
{
    return row * (numRows-1) + column;
}

bool Grid::CellIsValid(int row, int column)
{
    return  row < numRows && row >= 0 &&
            column < numCols && column >= 0;
}
