#include <Windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

void WaitForLeftPress()
{
    if (!GetAsyncKeyState(0x0002))
    {
        sleep(100);
        WaitForLeftPress();
    }
}

void LeftClickAtCoordinate(float const x,float const y)
{
    INPUT Inputs[3] = {0};

    Inputs[0].type = INPUT_MOUSE;
    Inputs[0].mi.dx = x; // desired X coordinate
    Inputs[0].mi.dy = y; // desired Y coordinate
    Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

    Inputs[1].type = INPUT_MOUSE;
    Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    Inputs[2].type = INPUT_MOUSE;
    Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(3, Inputs, sizeof(INPUT));
}

void CreateVirtualGameFromScreen()
{
    HDC dc = GetDC(NULL);
    COLORREF color = GetPixel(dc, 0, 0);
    ReleaseDC(NULL, dc);
}


//------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    //game settings
    int Columns = 11;
    int Rows = 12;
    int MaxSolverIterations = 2;


    //core info
    POINT LastMousePos;
    int GameScreenLocationLeft_X = 0;
    int GameScreenLocationLeft_Y = 0;
    
    int GameScreenLocationRight_X = 0;
    int GameScreenLocationRight_Y = 0;
    
    //Application start
    
    cout << "Welcome to turbo booster that probably will get your account banned!" << endl
    << "Click top left corner -> ";

    WaitForLeftPress();
    if (GetCursorPos(&LastMousePos))
    {
        GameScreenLocationLeft_X = LastMousePos.x;
        GameScreenLocationLeft_Y = LastMousePos.y;

        cout << LastMousePos.x << ", " << LastMousePos.y << endl;
    }

    cout << "Click top right corner -> ";
    
    WaitForLeftPress();
    if (GetCursorPos(&LastMousePos))
    {
        GameScreenLocationRight_X = LastMousePos.x;
        GameScreenLocationRight_Y = LastMousePos.y;

        cout << LastMousePos.x << ", " << LastMousePos.y << endl;
    }

    //Setup game
    CreateVirtualGameFromScreen();
    
    return 0;
}

