#include <windows.h>
#include "window.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
bool window::initWindow(int windowSizeX, int windowSizeY, LPCSTR windowTitle) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const char CLASS_NAME[] = "BaikalWindowClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);
    hwnd_ = CreateWindowEx(0,CLASS_NAME,windowTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,windowSizeX, windowSizeY,NULL,NULL,hInstance,NULL);
    if (hwnd_ == NULL) {
        return false;
    }
    ShowWindow(hwnd_, SW_SHOW);
    return true;
}
void window::runMessageLoop() {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
bool window::releaseWindow() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
        hwnd_ = NULL;
        return true;
    }
    return false;
}