// computergfx_lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>
void dda_xy(HDC dc, int x0, int y0, int x1, int y1,COLORREF color, bool swap) {
    double y = y0;
    for (double x = x0;x <= x1; x++) {//x-x0/x1-x0 = y - y0/y1 - y0
        y+= ((1.0 * y1 - y0) / (x1 - x0));
        if (swap)
            SetPixel(dc, round(y), round(x), color);
        else
            SetPixel(dc, round(x), round(y), color);
    }
}
void drawLineDDA(HDC dc,int x0, int y0, int x1, int y1 ) {
    
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    auto color = RGB(0, 255, 0);
    bool swap = dy * dy > dx * dx;


    if (dy <- dx) {
        int t = x1;
        x1 = x0;
        x0 = t;
        t = y0;
        y0 = y1;
        y1 = t;
    }
    


    if (swap)
      dda_xy(dc, y0, x0, y1, x1,color, swap);
    else
      dda_xy(dc, x0, y0, x1, y1,color, swap);

 
  
}
void bresenham_xy(HDC dc, int x0, int y0, int x1, int y1, COLORREF color, bool swap) {
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    int sx = x1 > x0 ? 1 : -1;
    int sy = y1 > y0 ? 1 : -1;
    int errdx = 0; 

    for (int x = x0, y = y0; x != x1;) {
        if (swap)
            SetPixel(dc, y, x, color);
        else
            SetPixel(dc, x, y, color);
        if (errdx*sy < dx) {
            // not changing height, moving horizontally
            x+=sx;
            errdx += dy;
            
        }
        else {
            //moving vertically, staying at the same x
            y+=sy;
            errdx -= dx*sy;
        }
    }
}
void drawLineBresenham(HDC dc, int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    auto color = RGB(255, 0, 0);
   
    bool swap = dy*dy>dx*dx;
    if (dy < -dx) {
        int t = x1;
        x1 = x0;
        x0 = t;
        t = y0;
        y0 = y1;
        y1 = t;
    }
    if (swap)
        bresenham_xy(dc, y0, x0, y1, x1, color, swap);
    else
        bresenham_xy(dc, x0, y0, x1, y1, color, swap);
}
int main()
{
    srand(time(NULL));
    HWND cwindow = GetConsoleWindow();
    HDC dc = GetDC(cwindow);
    SetWindowPos(cwindow, HWND_TOP, 0, 0, 300, 300, SWP_SHOWWINDOW|SWP_NOMOVE);
    float i = 0;
    while (1) {
        int x0 = rand()%300, y0 = rand()%300, x1 = rand()%300, y1 = rand()%300;
       // std::cout << x0 << ' ' << y0 << " to " << x1 << ' ' << y1 << std::endl;
        drawLineBresenham(dc, x0, y0, x1, y1);
        x0 = rand() % 300; y0 = rand() % 300; x1 = rand() % 300; y1 = rand() % 300;
        drawLineDDA(dc, x0, y0, x1, y1);

        Sleep(3000);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
