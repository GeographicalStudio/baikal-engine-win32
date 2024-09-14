#pragma once
#include <windows.h>
class window {
public:
    bool initWindow(int windowSizeX, int windowSizeY, LPCSTR windowTitle);
    void runMessageLoop();
    bool releaseWindow();
private:
    HWND hwnd_;
};