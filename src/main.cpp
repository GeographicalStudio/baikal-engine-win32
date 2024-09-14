#include <windows.h>
#include "window.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    window myWindow;
    if (!myWindow.initWindow(800, 600, "Baikal Window")) {
        return 0;
    }
    myWindow.runMessageLoop();
    myWindow.releaseWindow();
    return 0;
}