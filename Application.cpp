#include "Application.h"

Application::Application()
{
    grid = Grid();
    grid.grid2D[0][3] = 1;
    grid.grid2D[2][6] = 2;
    grid.grid2D[4][0] = 6;
    grid.grid2D[0][2] = 2;
}

void Application::Draw()
{
    grid.Draw();
}
