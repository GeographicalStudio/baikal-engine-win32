#pragma once
#include <windows.h>
class graphics {
public:
    graphics(HWND hwnd);
    ~graphics();
    void beginDraw();
    void endDraw();
    void drawRectangle(int x, int y, int width, int height, COLORREF color);
private:
    HWND hwnd_;
    HDC hdc_;
    HDC memDC_;
    HBITMAP bitmap_;
    HGDIOBJ oldBitmap_;
    PAINTSTRUCT ps_;
};