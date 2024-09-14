#include "graphics.h"
graphics::graphics(HWND hwnd) : hwnd_(hwnd), hdc_(nullptr), memDC_(nullptr), bitmap_(nullptr), oldBitmap_(nullptr) {
    hdc_ = GetDC(hwnd_);
    memDC_ = CreateCompatibleDC(hdc_);
    bitmap_ = CreateCompatibleBitmap(hdc_, 800, 600);
    oldBitmap_ = SelectObject(memDC_, bitmap_);
}
graphics::~graphics() {
    SelectObject(memDC_, oldBitmap_);
    DeleteObject(bitmap_);
    DeleteDC(memDC_);
    ReleaseDC(hwnd_, hdc_);
}
void graphics::beginDraw() {
    BeginPaint(hwnd_, &ps_);
}
void graphics::endDraw() {
    EndPaint(hwnd_, &ps_);
    BitBlt(hdc_, 0, 0, 800, 600, memDC_, 0, 0, SRCCOPY);
}
void graphics::drawRectangle(int x, int y, int width, int height, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(memDC_, brush);
    Rectangle(memDC_, x, y, x + width, y + height);
    SelectObject(memDC_, oldBrush);
    DeleteObject(brush);
}