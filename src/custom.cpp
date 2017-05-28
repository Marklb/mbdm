/* File custom.c
 * (custom control implementation)
 */

#include "custom.h"


static void
CustomPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    HRGN bgRgn;
    HBRUSH hBrush;

    hdc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &rect);

    bgRgn = CreateRectRgnIndirect(&rect);
    hBrush = CreateSolidBrush(RGB(60,0,80));
    // hBrush = CreateSolidBrush(RGB(30,0,50));
    // hBrush = CreateSolidBrush(RGB(0,0,0));
    FillRgn(hdc, bgRgn, hBrush);

    SetTextColor(hdc, RGB(0,0,0));
    SetBkMode(hdc, TRANSPARENT);
    DrawText(hdc, _T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    EndPaint(hwnd, &ps);
}


static LRESULT CALLBACK
CustomProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_PAINT:
            CustomPaint(hwnd);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void
CustomRegister(void)
{
    WNDCLASS wc = { 0 };

    wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = CustomProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = CUSTOM_WC;
    RegisterClass(&wc);
}

void
CustomUnregister(void)
{
    UnregisterClass(CUSTOM_WC, NULL);
}