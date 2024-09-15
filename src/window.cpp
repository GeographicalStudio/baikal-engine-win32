#include <windows.h>
#include "window.h"
#include "graphics.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static graphics* pGraphics = nullptr;
    switch (uMsg) {
    case WM_CREATE:
        pGraphics = new graphics(hwnd);
        return 0;
    case WM_PAINT:
        if (pGraphics) {
            pGraphics->beginDraw();
            pGraphics->drawRectangle(50, 50, 200, 100, RGB(255, 0, 0));
            pGraphics->endDraw();
        }
        return 0;
    case WM_DESTROY:
        if (pGraphics) {
            delete pGraphics;
            pGraphics = nullptr;
        }
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
    UpdateWindow(hwnd_);
    return true;
}
void window::runMessageLoop() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
void window::releaseWindow() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
        hwnd_ = nullptr;
    }
}