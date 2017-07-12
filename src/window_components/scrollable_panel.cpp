#include "scrollable_panel.h"

LRESULT ScrollablePanel::OnCreate()
{
    SetBackgroundColor(RGB(0,80,100));

    m_ScrollableContentPanelBottom = Panel::Create(GetHWND());
    m_ScrollableContentPanelBottom->SetBackgroundColor(RGB(0,120,0));
    m_ScrollableContentPanelBottom->SetPosition(0,0);
    m_ScrollableContentPanelBottom->SetSize(800,1000);
    ShowWindow(m_ScrollableContentPanelBottom->GetHWND(), SW_SHOW);

    m_ScrollableContentPanel = Panel::Create(m_ScrollableContentPanelBottom->GetHWND());
    m_ScrollableContentPanel->SetBackgroundColor(RGB(0,80,0));
    m_ScrollableContentPanel->SetPosition(0,0);
    m_ScrollableContentPanel->SetSize(800,1000);
    // m_ScrollableContentPanel->SetSize(800,600);
    // m_ScrollableContentPanel->SetSize(800,550);
    ShowWindow(m_ScrollableContentPanel->GetHWND(), SW_SHOW);


    m_VScrollbarWidth = 5;
    m_IsVScrollActive = false;
    m_VScrollbar = Scrollbar::Create(GetHWND());
    m_VScrollbar->SetContentPanel(m_ScrollableContentPanel);
    m_VScrollbar->SetWindowPanel(m_ScrollableContentPanelBottom);
    m_VScrollbar->SetButtonsActive(true);
    m_VScrollbar->SetButtonSize(10);
    m_VScrollbar->SetOrientation(Scrollbar::ORIENTATION_VERTICAL);
    ShowWindow(m_VScrollbar->GetHWND(), SW_HIDE);

    // m_ScrollableContentPanelOffset = -120;
    // m_ScrollableContentPanel = Panel::Create(GetHWND());
    // m_ScrollableContentPanel->SetBackgroundColor(RGB(0,80,0));
    // m_ScrollableContentPanel->SetSize(800,1000);
    // ShowWindow(m_ScrollableContentPanel->GetHWND(), SW_HIDE);
    // ShowWindow(GetHWND(), SW_SHOW);

    // UpdateScrollBarPosition();
    // UpdateScrollableContentPanelPosition();
    Update();

    return 0;
}

LRESULT ScrollablePanel::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            // UpdateScrollBarPosition();
            // UpdateScrollableContentPanelPosition();
            Update();
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

            // NMHDR nmh;
            // // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
            // nmh.code = 238;    // Message type defined by control.
            // nmh.idFrom = GetDlgCtrlID(GetHWND());
            // nmh.hwndFrom = GetHWND();
            // SendMessage(GetParent(GetHWND()),
            //     WM_NOTIFY,
            //     nmh.idFrom,
            //     (LPARAM)&nmh);

		}
        break;

        case WM_MOUSEWHEEL:
        {
            int incr = 0;
            ((short) HIWORD(wParam)< 0) ? incr-- : incr++;
            // printf("incr: %d\n", incr);
            if(incr > 0){
                m_VScrollbar->Decrement();
            }else if(incr < 0){
                m_VScrollbar->Increment();
            }
        }
        break;

        case WM_NOTIFY:
        {
            // printf("WM_NOTIFY: \n");
            // if(((HWND)wParam) == GetParent(GetHWND())){
            //     switch (((LPNMHDR)lParam)->code)
            //     {
            //         case WM_KEYDOWN:
            //         {
            //             printf("ScrollablePanel Notified WM_KEYDOWN\n");
            //
            //             return TRUE;
            //         }
            //         break;
            //
            //     }
            // }else{
            switch (((LPNMHDR)lParam)->code)
            {
                // case SBMSG_OFFSET_CHANGE:
                // {
                //     if (((LPNMHDR)lParam)->hwndFrom == m_VScrollbar->GetHWND()){
                //         printf("ScrollablePanel Notified\n");
                //         // m_MainPanel->SetVScroll(!m_MainPanel->IsVScrollActive());
                //         // RECT tmpRect;
                //         // GetClientRect(m_ScrollableContentPanel->GetHWND(),&tmpRect);
                //         // InvalidateRect(m_ScrollableContentPanel->GetHWND(),&tmpRect,FALSE);
                //         UpdateScrollableContentPanelPosition();
                //         return TRUE;
                //     }
                // }
                // break;

                case WM_KEYDOWN:
                {
                    if (((LPNMHDR)lParam)->hwndFrom == GetParent(GetHWND())){
                        // printf("ScrollablePanel Notified WM_KEYDOWN\n");
                        switch(((KBNMHDR *)lParam)->vkCode)
                        {
                            case VK_UP:
                            {
                                // printf("VK_UP\n");
                                // m_VScrollbar->DecrementPageOffset();
                            }
                            break;

                            case VK_DOWN:
                            {
                                // printf("VK_DOWN\n");
                                // m_VScrollbar->IncrementPageOffset();
                            }
                            break;
                        }
                        return TRUE;
                    }
                }
                break;

            }
            // }
            break;
        }
        break;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

ScrollablePanel *ScrollablePanel::Create(HWND hWndParent)
{
    ScrollablePanel *self = new ScrollablePanel();
    if (self && self->WinCreateWindow(0,
        //  TEXT("Panel"), WS_CHILD | WS_HSCROLL | WS_VSCROLL,
        TEXT("ScrollablePanel"), WS_CHILD | WS_CLIPCHILDREN,
        20, 20, 200, 200, hWndParent, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

void ScrollablePanel::PaintContent(PAINTSTRUCT *pps)
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

Panel* ScrollablePanel::GetPanel(void)
{
    return m_ScrollableContentPanel;
}

Scrollbar* ScrollablePanel::GetVScrollBar(void)
{
    return m_VScrollbar;
}

void ScrollablePanel::SetVScroll(bool isActive)
{
    // if(isActive == true && m_VScrollbar == NULL){
    //     m_VScrollbar = Scrollbar::Create(GetHWND());
    //     UpdateScrollBarPosition();
    // }else if(isActive == false && m_VScrollbar != NULL){
    //     delete m_VScrollbar;
    //     m_VScrollbar = NULL;
    // }
    m_IsVScrollActive = isActive;
    if(m_IsVScrollActive == true){
        // UpdateScrollBarPosition();
        // UpdateScrollableContentPanelPosition();
        ShowWindow(m_VScrollbar->GetHWND(), SW_SHOW);
        // ShowWindow(m_ScrollableContentPanel->GetHWND(), SW_SHOW);
    }else{
        // UpdateScrollableContentPanelPosition();
        ShowWindow(m_VScrollbar->GetHWND(), SW_HIDE);
        // ShowWindow(m_ScrollableContentPanel->GetHWND(), SW_HIDE);
    }
    Update();
}

bool ScrollablePanel::IsVScrollActive(void)
{
    return m_IsVScrollActive;
}

void ScrollablePanel::Update(void)
{
    // printf("ScrollablePanel::Update\n");
    RECT rect;
    GetClientRect(GetHWND(), &rect);

    if(m_IsVScrollActive == false){
        // printf("m_IsVScrollActive: false\n");
        m_ScrollableContentPanelBottom->SetPosition(0,0);
        m_ScrollableContentPanelBottom->SetSize(
            rect.right-rect.left,
            rect.bottom-rect.top);
    }else{
        // printf("m_IsVScrollActive: true\n");
        m_ScrollableContentPanelBottom->SetPosition(0,0);
        m_ScrollableContentPanelBottom->SetSize(
            (rect.right-rect.left)-m_VScrollbarWidth,
            rect.bottom-rect.top);

        m_VScrollbar->SetPosition(rect.right-rect.left-m_VScrollbarWidth,0);
        m_VScrollbar->SetSize(m_VScrollbarWidth,rect.bottom-rect.top);

        RECT contentRect;
        GetClientRect(m_ScrollableContentPanel->GetHWND(), &contentRect);
        // printf("contentRect: top: %d, right: %d, bottom: %d, left: %d\n",
        //     contentRect.top, contentRect.right, contentRect.bottom, contentRect.left);
        m_VScrollbar->SetContentSize(contentRect.bottom-contentRect.top);

        RECT windowRect;
        GetClientRect(m_ScrollableContentPanelBottom->GetHWND(), &windowRect);
        // printf("windowRect: top: %d, right: %d, bottom: %d, left: %d\n",
        //     windowRect.top, windowRect.right, windowRect.bottom, windowRect.left);
        m_VScrollbar->SetWindowSize(windowRect.bottom-windowRect.top);

        m_VScrollbar->Update();

    }
}

// void ScrollablePanel::UpdateScrollBarPosition(void)
// {
//     if(m_IsVScrollActive == false || m_VScrollbar == NULL) return;
//     // Horizonal scrollbar
//     RECT rect;
//     GetClientRect(GetHWND(), &rect);
//     // Left side
//     // m_VScrollbar->SetPosition(0,0);
//     // m_VScrollbar->SetSize(m_VScrollbarWidth,rect.bottom-rect.top);
//     // Right side
//     m_VScrollbar->SetPosition(rect.right-rect.left-m_VScrollbarWidth,0);
//     m_VScrollbar->SetSize(m_VScrollbarWidth,rect.bottom-rect.top);
//
//     RECT contentRect;
//     GetClientRect(m_ScrollableContentPanel->GetHWND(), &contentRect);
//     m_VScrollbar->SetContentSize(contentRect.bottom-contentRect.top);
//
//     RECT windowRect;
//     GetClientRect(m_ScrollableContentPanelBottom->GetHWND(), &windowRect);
//     m_VScrollbar->SetWindowSize(windowRect.bottom-windowRect.top);
//
//     // RECT tmpRect;
//     // GetClientRect(m_VScrollbar->GetHWND(),&tmpRect);
//     // InvalidateRect(m_VScrollbar->GetHWND(),&tmpRect,FALSE);
// }
//
// void ScrollablePanel::UpdateScrollableContentPanelPosition(void)
// {
//     printf("ScrollablePanel::UpdateScrollableContentPanelPosition\n");
//     RECT rect;
//     GetClientRect(GetHWND(), &rect);
//
//     if(m_IsVScrollActive == false){
//         m_ScrollableContentPanelBottom->SetPosition(0,0);
//         m_ScrollableContentPanelBottom->SetSize(
//             rect.right-rect.left,
//             rect.bottom-rect.top);
//     }else{
//         m_ScrollableContentPanelBottom->SetPosition(0,0);
//         m_ScrollableContentPanelBottom->SetSize(
//             (rect.right-rect.left)-m_VScrollbarWidth,
//             rect.bottom-rect.top);
//     }
//
//     // RECT rect;
//     // GetClientRect(GetHWND(), &rect);
//     // m_ScrollableContentPanel->SetPosition(0,0-m_VScrollbar->GetContentPosition());
//     // m_ScrollableContentPanelBottom->SetSize(rect.right-rect.left-m_VScrollbarWidth,
//     //     rect.bottom-rect.top);
//
//     // EnumChildWindows(m_ScrollableContentPanel->GetHWND(), [](HWND hwnd, LPARAM lParam) -> BOOL {
//     //     Panel *pnl = (Panel *)lParam;
//     //     RECT rParent;
//     //     GetWindowRect(pnl->GetHWND(), &rParent);
//     //     // printf("%d, %d,%d,%d,%d\n", (int)pnl->GetHWND(),
//     //     //     rParent.top, rParent.right, rParent.bottom, rParent.left);
//     //
//     //     RECT r;
//     //     GetWindowRect(hwnd, &r);
//     //     // printf("%d, %d,%d,%d,%d\n", (int)hwnd,
//     //     //     r.top, r.right, r.bottom, r.left);
//     //
//     //     int top = r.top - rParent.top;
//     //     int bottom = top+(r.bottom - r.top);
//     //     printf("\t%d %d\n", top, bottom);
//     //
//     //     RECT cRect;
//     //     GetClientRect(pnl->GetHWND(),&cRect);
//     //     pnl->SetSize(cRect.right-cRect.left,bottom);
//     //     return TRUE;
//     // }, (LPARAM)m_ScrollableContentPanel);
//
//     // GetClientRect(m_ScrollableContentPanel->GetHWND(), &rect);
//     // m_VScrollbar->SetContentSize(rect.bottom-rect.top);
//     // m_VScrollbar->SetWindowSize(rect.bottom-rect.top);
//     // m_VScrollbar->SetPageHeight(2350);
//     // m_VScrollbar->SetPageOffset(m_ScrollableContentPanelOffset)
//
// }
