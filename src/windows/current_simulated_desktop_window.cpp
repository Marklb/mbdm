#include "current_simulated_desktop_window.h"

LRESULT CurrentSimulatedDesktopWindow::OnCreate()
{
    m_Text.assign("Untitled Simulated Desktop");

    SetWindowPos(GetHWND(), HWND_TOPMOST, NULL, NULL, NULL, NULL,
        SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);
    return 0;
}

LRESULT CurrentSimulatedDesktopWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CREATE:
            return OnCreate();

        case WM_NCDESTROY:
        {
            // Death of the root window ends the thread
            PostQuitMessage(0);
        }
        break;

        case WM_SIZE:
        {
            // if (m_hWndChild) {
            //     SetWindowPos(m_hWndChild, NULL, 0, 0,
            //                  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),
            //                  SWP_NOZORDER | SWP_NOACTIVATE);
            // }
            // if(m_MainPanel){
            //     m_MainPanel->SetPosition(0,0);
            //     m_MainPanel->SetSize(400,500+50);
            // }
        }
        return 0;

        case WM_SETFOCUS:
        {
            // if (m_hWndChild) {
            //     SetFocus(m_hWndChild);
            // }
        }
        return 0;

        case WM_LBUTTONDOWN:
        {
		}
        break;

        case WM_KEYDOWN:
        {
            // printf("KeyDown sw\n");
            switch(wParam)
            {
                case VK_UP:
                case VK_DOWN:
                {

                }
                break;
            }
        }
        break;

        case WM_PARENTNOTIFY:
        {
            // printf("WM_PARENTNOTIFY: \n");
            // switch(wParam)
            // {
            //     case WM_LBUTTONDOWN:
            //     {
            //         printf("Toggle\n");
            //     }
            //     break;
            // }
        }
        break;

        case WM_NOTIFY:
        {
            // printf("WM_NOTIFY: \n");
            switch (((LPNMHDR)lParam)->code)
            {


            }
            break;
        }
        break;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

CurrentSimulatedDesktopWindow *CurrentSimulatedDesktopWindow::Create()
{
    // int x = CW_USEDEFAULT;
    // int y = CW_USEDEFAULT;
    // int w = CW_USEDEFAULT;
    // int h = CW_USEDEFAULT;

    int x = 10;
    int y = 10;
    int w = 400;
    int h = 700;

    CurrentSimulatedDesktopWindow *self = new CurrentSimulatedDesktopWindow();
    if (self && self->WinCreateWindow(0,
        TEXT("CurrentSimulatedDesktopWindow"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // | WS_HSCROLL | WS_VSCROLL,
        x, y, w, h, NULL, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

void CurrentSimulatedDesktopWindow::PaintContent(PAINTSTRUCT *pps)
{
    // HDC hdc = GetDC(GetHWND());
    HDC hdc = pps->hdc;
    HWND hWnd = GetHWND();

    RECT rect;
    GetClientRect(hWnd, &rect);
    // HBRUSH hBrush = CreateSolidBrush(RGB(60,0,80));
    // HBRUSH hBrush = CreateSolidBrush(RGB(30,0,50));
    HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));
    FillRect(hdc,&rect,hBrush);


    SetBkColor(hdc, RGB(0,0,0));
    SetTextColor(hdc, RGB(80,0,100));
    // RGB(60,40,150)
    DrawText(hdc, m_Text.c_str(), m_Text.size(), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);


    HBRUSH hBrushBorder = CreateSolidBrush(RGB(60,0,80));

    RECT rectBorderTop;
    GetClientRect(hWnd, &rectBorderTop);
    rectBorderTop.bottom = 2;
    FillRect(hdc,&rectBorderTop,hBrushBorder);

    RECT rectBorderBottom;
    GetClientRect(hWnd, &rectBorderBottom);
    rectBorderBottom.top = rectBorderBottom.bottom-2;
    FillRect(hdc,&rectBorderBottom,hBrushBorder);

    RECT rectBorderLeft;
    GetClientRect(hWnd, &rectBorderLeft);
    rectBorderLeft.right = 2;
    FillRect(hdc,&rectBorderLeft,hBrushBorder);

    RECT rectBorderRight;
    GetClientRect(hWnd, &rectBorderRight);
    rectBorderRight.left = rectBorderRight.right-2;
    FillRect(hdc,&rectBorderRight,hBrushBorder);


    DeleteObject(hBrush);
    DeleteObject(hBrushBorder);
}

void CurrentSimulatedDesktopWindow::SetText(char *text)
{
    m_Text.assign(text);
}
