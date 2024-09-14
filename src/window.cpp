#include <windows.h>
#include "window.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    window* pWindow;
    if (uMsg == WM_NCCREATE) {
        pWindow = static_cast<window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
    } else {
        pWindow = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    if (pWindow) {
        switch (uMsg) {
        case WM_PAINT: {
            HDC hdc = BeginPaint(hwnd, &pWindow->ps_);
            pWindow->present();
            EndPaint(hwnd, &pWindow->ps_);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
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
    hwnd_ = CreateWindowEx(0,CLASS_NAME,windowTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,windowSizeX, windowSizeY,NULL,NULL,hInstance,this);
    if (hwnd_ == NULL) return false;
    windowSizeX_ = windowSizeX;
    windowSizeY_ = windowSizeY;
    framebuffer_ = new COLORREF[windowSizeX_ * windowSizeY_];
    ShowWindow(hwnd_, SW_SHOW);
    hdc_ = GetDC(hwnd_);
    return true;
}
void window::drawPixel(int x, int y, COLORREF color) {
    if (x >= 0 && x < windowSizeX_ && y >= 0 && y < windowSizeY_) {
        framebuffer_[y * windowSizeX_ + x] = color;
    }
}
void window::present() {
    HDC hdc = GetDC(hwnd_);
    if (hdc) {
        for (int y = 0; y < windowSizeY_; ++y) {
            for (int x = 0; x < windowSizeX_; ++x) {
                SetPixel(hdc, x, y, framebuffer_[y * windowSizeX_ + x]);
            }
        }
        ReleaseDC(hwnd_, hdc);
    }
}
bool window::releaseWindow() {
    if (hdc_) ReleaseDC(hwnd_, hdc_);
    if (hwnd_) DestroyWindow(hwnd_);
    hwnd_ = NULL;
    delete[] framebuffer_;
    framebuffer_ = nullptr;
    return true;
}