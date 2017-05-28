#include "panel.h"

LRESULT Panel::OnCreate()
{
    // ShowWindow(GetHWND(), SW_SHOW);
    return 0;
}

LRESULT Panel::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

        case WM_PARENTNOTIFY:
        {
            switch(LOWORD(wParam))
            {
                case WM_CREATE:
                {
                    printf("WM_PARENTNOTIFY :: WM_CREATE\n");
                    RECT tmp;
                    GetClientRect((HWND)lParam, &tmp);
                    printf("\t%d, %d, %d, %d\n", tmp.top, tmp.right, tmp.bottom, tmp.left);
                }
                break;
            }
        }
        break;

        // case WM_SETFOCUS:
        //   if (m_hWndChild) {
        //     SetFocus(m_hWndChild);
        //   }
        //   return 0;

        case WM_LBUTTONDOWN: {
            // printf("Clicked panel\n");
			// m_Borderless = !m_Borderless;
            // SetWindowPos(GetHWND(), NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

            // NMHDR nmh;
            // // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
            // nmh.code = 238;    // Message type defined by control.
            // nmh.idFrom = GetDlgCtrlID(GetHWND());
            // nmh.hwndFrom = GetHWND();
            // SendMessage(GetParent(GetHWND()),
            //     WM_NOTIFY,
            //     nmh.idFrom,
            //     (LPARAM)&nmh);

			break;
		}
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

Panel *Panel::Create(HWND hWndParent)
{
    Panel *self = new Panel();
    if (self && self->WinCreateWindow(0,
        //  TEXT("Panel"), WS_CHILD | WS_HSCROLL | WS_VSCROLL,
        TEXT("Panel"), WS_CHILD | WS_CLIPCHILDREN,
        20, 20, 200, 200, hWndParent, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

void Panel::PaintContent(PAINTSTRUCT *pps)
{
  // HDC hdc = GetDC(GetHWND());
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
  //   SetBkColor(hdc, RGB(0,0,0));
  //   SetDCBrushColor(hdc, RGB(0,0,0));
  //   SetTextColor(hdc, RGB(80,0,100));
  //   bgRgn = CreateRectRgnIndirect(&rect);
  //   hBrush = CreateSolidBrush(RGB(0,0,0));
  //   FillRgn(hdc, bgRgn, hBrush);
  //   // DrawText(hdc, data->text, strlen(data->text), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
  //   DrawText(hdc, _T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
  //   // std::cout << "YO" << std::endl;
}
























// int WINAPI
// WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int nShowCmd)
// {
//  g_hinst = hinst;

//  if (SUCCEEDED(CoInitialize(NULL))) {
//   InitCommonControls();

//   SettingsWindow *prw = SettingsWindow::Create();
//   if (prw) {
//    ShowWindow(prw->GetHWND(), nShowCmd);
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0)) {
//     TranslateMessage(&msg);
//     DispatchMessage(&msg);
//    }
//   }
//   CoUninitialize();
//  }
//  return 0;
// }
