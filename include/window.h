#pragma once
#include <windows.h>
class window {
public:
    bool initWindow(int windowSizeX, int windowSizeY, LPCSTR windowTitle);
    void runMessageLoop();
    bool releaseWindow();
    void drawPixel(int x, int y, COLORREF color);
    void present();
    HWND hwnd_;
    HDC hdc_;
    PAINTSTRUCT ps_;
    int windowSizeX_;
    int windowSizeY_;
    COLORREF* framebuffer_;
};