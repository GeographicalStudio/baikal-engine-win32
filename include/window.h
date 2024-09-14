#pragma once
#include <windows.h>
class window {
public:
    bool initWindow(int windowSizeX, int windowSizeY);
    bool updateWindow();
    bool releaseWindow();
};