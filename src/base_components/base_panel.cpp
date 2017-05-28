#include "base_panel.h"





void BasePanel::Register()
{
    WNDCLASS wc;
    wc.style         = 0;
    wc.lpfnWndProc   = BasePanel::s_WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = g_hInst;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = ClassName();

    WinRegisterClass(&wc);
}

LRESULT CALLBACK BasePanel::s_WndProc(HWND hWnd,
  UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BasePanel *self;
    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        self = reinterpret_cast<BasePanel *>(lpcs->lpCreateParams);
        self->m_hWnd = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(self));
    } else {
        self = reinterpret_cast<BasePanel *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }
    if (self) {
        return self->HandleMessage(uMsg, wParam, lParam);
    } else {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

LRESULT BasePanel::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lres;

    switch (uMsg) {
        case WM_NCDESTROY:
        {
            lres = DefWindowProc(m_hWnd, uMsg, wParam, lParam);
            SetWindowLongPtr(m_hWnd, GWLP_USERDATA, 0);
            delete this;
            return lres;
        }

        case WM_PAINT:
        {
            OnPaint();
            return 0;
        }

        case WM_PRINTCLIENT:
        {
            OnPrintClient(reinterpret_cast<HDC>(wParam));
            return 0;
        }

        // case WM_ERASEBKGND:
        //     return (LRESULT)1; // Say we handled it.
    }

    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void BasePanel::OnPaint()
{
    PAINTSTRUCT ps;
    BeginPaint(m_hWnd, &ps);

    RECT clientRect;
    GetClientRect(GetHWND(),&clientRect);

    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;

    HDC hdc = ps.hdc;
    HDC bufDC;
    HBITMAP bufBMP;

    bufDC = CreateCompatibleDC(hdc);
    bufBMP = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(bufDC, bufBMP);

    ps.hdc = bufDC;


    PaintBackground(&ps);
    PaintContent(&ps);


    BitBlt(hdc, 0, 0, width, height, bufDC, 0, 0, SRCCOPY);

    ps.hdc = hdc;

    DeleteObject(bufBMP);
    DeleteDC(bufDC);

    EndPaint(m_hWnd, &ps);
}

void BasePanel::OnPrintClient(HDC hdc)
{
    PAINTSTRUCT ps;
    ps.hdc = hdc;
    GetClientRect(m_hWnd, &ps.rcPaint);
    // PaintBackground();
    // PaintContent(&ps);
}

void BasePanel::PaintBackground(PAINTSTRUCT *pps)
{
    if(m_BgColor == COLOR_NONE) return;

    // HDC hdc = GetDC(GetHWND());
    HDC hdc = pps->hdc;
    HWND hWnd = GetHWND();

    RECT rect;
    GetClientRect(hWnd, &rect);
    // HRGN bgRgn = CreateRectRgnIndirect(&rect);
    // hBrush = CreateSolidBrush(RGB(60,0,80));
    // hBrush = CreateSolidBrush(RGB(30,0,50));
    // hBrush = CreateSolidBrush(RGB(0,0,0));
    HBRUSH hBrush = CreateSolidBrush(m_BgColor);
    // FillRgn(hdc, bgRgn, hBrush);
    FillRect(hdc,&rect,hBrush);
    // ReleaseDC(hWnd,hdc);
    DeleteObject(hBrush);
}

void BasePanel::SetPosition(int x, int y)
{
    SetWindowPos(GetHWND(),NULL,x,y,NULL,NULL,SWP_NOACTIVATE | SWP_NOSIZE
        | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void BasePanel::SetSize(int w, int h)
{
    SetWindowPos(GetHWND(),NULL,NULL,NULL,w,h,SWP_NOACTIVATE | SWP_NOMOVE
        | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void BasePanel::SetBackgroundColor(COLORREF color)
{
    // printf("R: %i, G: %i, B: %i\n", GetRValue(color), GetGValue(color), GetBValue(color));
    m_BgColor = color;
}
