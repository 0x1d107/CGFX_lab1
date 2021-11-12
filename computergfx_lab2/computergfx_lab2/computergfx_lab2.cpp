// computergfx_lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include <Windows.h>
struct Circle { 
    int x; int y; int r; 
    int point_dist(int x, int y) {
        return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) - this->r * this->r;
    }
    int next_dist(int d, int x) {
        return d + 2 * (x - this->x) + 1;
    }
};

void drawLine(HDC dc, int x1, int x2, int y, COLORREF color,COLORREF intersection, Circle other) {
    for (int x = min(x1,x2), xr=max(x1,x2),d = other.point_dist(x,y); x <= xr; x++) {

        if (d<=0)
            SetPixel(dc, x, y, intersection);
        else
            SetPixel(dc, x, y, color);
        d = other.next_dist(d, x);
        
    }
}
void drawpixel_xy(HDC dc, int x0, int y0,int x,int y,COLORREF fill, Circle other) {
    COLORREF color = fill;
    COLORREF bg = RGB(0, 0, 255);
    drawLine(dc, 2 * x0 - x, x, y, color,bg,other);
    drawLine(dc, 2 * x0 -x,x, 2 * y0 - y, color,bg,other);
   
    x -= x0;
    y -= y0;
    x ^= y;
    y ^= x;
    x ^= y;
    x += x0;
    y += y0;
    drawLine(dc, 2 * x0 - x, x, y, color,bg,other);
    drawLine(dc, 2 * x0 - x, x, 2 * y0 - y, color,bg,other);
    
}

void drawCircle(HDC dc, int x0, int y0, int r,COLORREF color,Circle other) {

    int err = 0;
    for (int y = y0, x = x0 + r; y - y0 <= x - x0; y++) {
        int dx = x - x0;
        int dy = y - y0;
        drawpixel_xy(dc, x0, y0, x, y,color,other);
        int u = err + 2 * dy + 1;
        int v = -2 * dx + 1;
        if ((2*u+v)*v<0) {
            x--;
            err += -2 * dx + 1;
        }
        err += 2 * (dy)+1;
        
    }
}

int main()
{
    
    srand(time(NULL));
    HWND cw = GetConsoleWindow();
    HDC hdc = GetDC(cw);
    
    int x1 = 100;
    int y1 = 100;
    int r1 = 50;
    int r2 = 50;
    int x2 = 150;
    int y2 = 150;
    COLORREF c1 = RGB(255, 0, 0);
    COLORREF c2 = RGB(0, 255, 0);
    drawCircle(hdc, x1, y1, r1, c1, Circle{x2,y2,0});
    Sleep(1000);
    drawCircle(hdc, x2, y2, r2, c2, Circle{x1,y1,r1});

    getc(stdin);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
