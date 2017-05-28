#include "button.h"

LRESULT Button::OnCreate()
{
    m_Text.assign("");
    SetButtonTextColor(RGB(60,40,150));
    SetBackgroundColor(RGB(0,0,0));
    // ShowWindow(GetHWND(), SW_SHOW);
    return 0;
}

LRESULT Button::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CREATE:
            return OnCreate();

        // case WM_NCDESTROY:
        //  // Death of the root window ends the thread
        //  PostQuitMessage(0);
        //  break;

        // case WM_SIZE:
        //   if (m_hWndChild) {
        //     SetWindowPos(m_hWndChild, NULL, 0, 0,
        //                  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),
        //                  SWP_NOZORDER | SWP_NOACTIVATE);
        //   }
        //   return 0;
        case WM_SIZE:
        {

            break;
        }

        // case WM_SETFOCUS:
        //   if (m_hWndChild) {
        //     SetFocus(m_hWndChild);
        //   }
        //   return 0;

        case WM_LBUTTONDOWN: {
            // printf("Clicked panel\n");
			// m_Borderless = !m_Borderless;
            // SetWindowPos(GetHWND(), NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

            NMHDR nmh;
            // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
            nmh.code = WM_LBUTTONDOWN;    // Message type defined by control.
            nmh.idFrom = GetDlgCtrlID(GetHWND());
            nmh.hwndFrom = GetHWND();
            SendMessage(GetParent(GetHWND()),
                WM_NOTIFY,
                nmh.idFrom,
                (LPARAM)&nmh);

			break;
		}
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

Button *Button::Create(HWND hWndParent)
{
    Button *self = new Button();
    if (self && self->WinCreateWindow(0,
        //  TEXT("Button"), WS_CHILD | WS_HSCROLL | WS_VSCROLL,
        TEXT("Button"), WS_CHILD,
        20, 20, 200, 50, hWndParent, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

void Button::PaintContent(PAINTSTRUCT *pps)
{
    //   HDC hdc = GetDC(GetHWND());
    HDC hdc = pps->hdc;
    // if(pps->hdc != NULL){
    //     hdc = pps->hdc;
    // }
    // RECT clientRect;
    // RECT rectInner;
    // HRGN bgRgn;
    // HBRUSH hBrush;
    //
    // HWND hWnd = GetHWND();
    // // Draw the border
    //   RECT rect;
    //   GetClientRect(hWnd, &rect);
    //   bgRgn = CreateRectRgnIndirect(&rect);
    //   hBrush = CreateSolidBrush(RGB(60,0,80));
    //   // hBrush = CreateSolidBrush(RGB(30,0,50));
    //   // hBrush = CreateSolidBrush(RGB(0,0,0));
    //   FillRgn(hdc, bgRgn, hBrush);
    //
    //   // int borderSize = 2;
    //   // mb_draw_DrawRectBorder(hdc, &rect, borderSize, RGB(0,50,100), MB_DRAW_BORDER_STYLE_INSET);
    //   //
    //   // if(data->tier != NULL){
    //   //   // RECT titleRect = {rect.left+borderSize, rect.top+borderSize, rect.right-rect.left-borderSize, titleHeight};
    //   //   RECT textRect = {rect.left+borderSize, rect.top+borderSize, rect.right-borderSize, rect.bottom-borderSize};
    //   //   SetBkColor(hdc, RGB(0,0,0));
    //   //   SetDCBrushColor(hdc, RGB(0,0,0));
    //   //   SetTextColor(hdc, RGB(80,0,100));
    //   //   bgRgn = CreateRectRgnIndirect(&textRect);
    //   //   hBrush = CreateSolidBrush(RGB(0,0,0));
    //   //   FillRgn(hdc, bgRgn, hBrush);
    //   //   DrawText(hdc, data->tier->name, strlen(data->tier->name), &textRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    //   // }
    //

    RECT rect;
    GetClientRect(GetHWND(), &rect);
    SetBkColor(hdc, RGB(0,0,0));
    // SetDCBrushColor(hdc, RGB(0,0,0));
    SetTextColor(hdc, RGB(80,0,100));
    // bgRgn = CreateRectRgnIndirect(&rect);
    // hBrush = CreateSolidBrush(RGB(0,0,0));
    // FillRgn(hdc, bgRgn, hBrush);
    // DrawText(hdc, data->text, strlen(data->text), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    DrawText(hdc, m_Text.c_str(), m_Text.size(), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    // DrawText(hdc, _T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    // std::cout << "YO" << std::endl;
    ReleaseDC(GetHWND(),hdc);
}

void Button::SetText(char *text)
{
    m_Text.assign(text);
}

void Button::SetButtonTextColor(COLORREF color)
{
    m_TextColor = color;
}
