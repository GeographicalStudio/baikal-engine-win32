#pragma once
#include <windows.h>
#include <vector>
#include <functional>
class graphics {
public:
    graphics(HWND hwnd);
    ~graphics();
    void beginDraw();
    void endDraw();
    void drawRectangle(int x, int y, int width, int height, COLORREF color);
    void drawCall();
    enum class DrawCommandType {
        Rectangle
    };
    struct DrawCommand {
        DrawCommandType type;
        int x, y, width, height;
        COLORREF color;
    };
private:
    HWND hwnd_;
    HDC hdc_;
    HDC memDC_;
    HBITMAP bitmap_;
    HGDIOBJ oldBitmap_;
    PAINTSTRUCT ps_;
    std::vector<DrawCommand> drawStack_;
};