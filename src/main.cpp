#include <windows.h>
#include "window.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    window window;
    if (!window.initWindow(800, 600, "Baikal Window")) {
        return 0;
    }
    window.runMessageLoop();
    window.releaseWindow();
    return 0;
}