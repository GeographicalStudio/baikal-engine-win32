#pragma once
#include <windows.h>
class window {
public:
    bool initWindow(int windowSizeX, int windowSizeY, LPCSTR windowTitle);
    void runMessageLoop();
    void releaseWindow();
    HWND hwnd_;
    HDC hdc_;
    PAINTSTRUCT ps_;
};