#include "settings_window.h"

LRESULT SettingsWindow::OnCreate()
{
    m_MainPanel = ScrollablePanel::Create(GetHWND());
    m_MainPanel->SetPosition(0,0);
    m_MainPanel->SetSize(300,500);
    m_MainPanel->SetBackgroundColor(RGB(30,0,80));
    // m_MainPanel->SetBackgroundColor(RGB(0,0,0));
    m_MainPanel->SetVScroll(true);


    m_TestButton1 = Button::Create(m_MainPanel->GetPanel()->GetHWND());
    // m_TestButton1->SetPosition(10,100);
    m_TestButton1->SetPosition(0,0);
    m_TestButton1->SetSize(300,50);
    m_TestButton1->SetText("Test Button 1");

    m_TestButton2 = Button::Create(m_MainPanel->GetPanel()->GetHWND());
    m_TestButton2->SetPosition(60,300);
    m_TestButton2->SetText("Test Button 2");

    m_TestButton3 = Button::Create(m_MainPanel->GetPanel()->GetHWND());
    m_TestButton3->SetPosition(40,550);
    m_TestButton3->SetText("Test Button 3");

    m_TestButton4 = Button::Create(m_MainPanel->GetPanel()->GetHWND());
    // m_TestButton4->SetPosition(100,800+1000);
    // m_TestButton4->SetPosition(100,890);
    m_TestButton4->SetPosition(100,2300);
    m_TestButton4->SetSize(300,50);
    m_TestButton4->SetText("Test Button 4");



    m_TestButton = Button::Create(GetHWND());
    m_TestButton->SetPosition(405,5);
    m_TestButton->SetText("Toggle Scrollbar");

    m_TestButton5 = Button::Create(GetHWND());
    m_TestButton5->SetPosition(405,60);
    m_TestButton5->SetText("Print Size");



    ShowWindow(m_MainPanel->GetHWND(),SW_SHOW);
    ShowWindow(m_TestButton1->GetHWND(),SW_SHOW);
    ShowWindow(m_TestButton2->GetHWND(),SW_SHOW);
    ShowWindow(m_TestButton3->GetHWND(),SW_SHOW);
    ShowWindow(m_TestButton4->GetHWND(),SW_SHOW);
    ShowWindow(m_TestButton->GetHWND(),SW_SHOW);
    ShowWindow(m_TestButton5->GetHWND(),SW_SHOW);
    return 0;
}

LRESULT SettingsWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

        // case WM_NCCALCSIZE: {
    		// 	// this kills the window frame and title bar we added with
    		// 	// WS_THICKFRAME or WS_CAPTION
    		// 	if (m_Borderless) return 0;
    		// 	break;
    		// }

        case WM_SIZE:
        {
            if (m_hWndChild) {
                SetWindowPos(m_hWndChild, NULL, 0, 0,
                             GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),
                             SWP_NOZORDER | SWP_NOACTIVATE);
            }
            if(m_MainPanel){
                m_MainPanel->SetPosition(0,0);
                // m_MainPanel->SetSize(400,500+50);
                RECT r;
                GetClientRect(GetHWND(), &r);
                RECT panelRect;
                GetClientRect(m_MainPanel->GetHWND(), &panelRect);
                m_MainPanel->SetSize(
                    panelRect.right - panelRect.left,
                    r.bottom - r.top);
            }
        }
        return 0;

        case WM_SETFOCUS:
        {
            if (m_hWndChild) {
                SetFocus(m_hWndChild);
            }
        }
        return 0;

        case WM_LBUTTONDOWN: {
            // printf("Clicked\n");
			// m_Borderless = !m_Borderless;
            // SetWindowPos(GetHWND(), NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
			break;
		}

        case WM_KEYDOWN:
        {
            // printf("KeyDown sw\n");
            switch(wParam)
            {
                case VK_UP:
                case VK_DOWN:
                {
                    // m_HScrollbar->IncrementPageOffset();
                    // NMHDR nmh;
                    // // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
                    // nmh.code = WM_KEYDOWN;    // Message type defined by control.
                    // nmh.idFrom = GetDlgCtrlID(GetHWND());
                    // nmh.hwndFrom = GetHWND();
                    // SendMessage(m_MainPanel->GetHWND(),
                    //     WM_NOTIFY,
                    //     nmh.idFrom,
                    //     (LPARAM)&nmh);

                    KBNMHDR kbnmh;
                    // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
                    kbnmh.nmh.code = WM_KEYDOWN;    // Message type defined by control.
                    kbnmh.nmh.idFrom = GetDlgCtrlID(GetHWND());
                    kbnmh.nmh.hwndFrom = GetHWND();
                    kbnmh.vkCode = wParam;
                    SendMessage(m_MainPanel->GetHWND(),
                        WM_NOTIFY,
                        kbnmh.nmh.idFrom,
                        (LPARAM)&kbnmh);
                }
                break;

                // {
                //     // m_HScrollbar->DecrementPageOffset();
                // }
                // break;
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
                case WM_LBUTTONDOWN:
                {
                    if (((LPNMHDR)lParam)->hwndFrom == m_TestButton->GetHWND()){
                        printf("Toggle\n");
                        m_MainPanel->SetVScroll(!m_MainPanel->IsVScrollActive());
                        return TRUE;
                    }else if (((LPNMHDR)lParam)->hwndFrom == m_TestButton5->GetHWND()){
                        // printf("Toggle\n");
                        // m_MainPanel->SetHScroll(!m_MainPanel->IsHScrollActive());
                        Panel *tmp = m_MainPanel->GetPanel();
                        RECT rect;
                        GetClientRect(tmp->GetHWND(), &rect);
                        printf("Y: %d, Height: %d\n", rect.top, (rect.bottom-rect.top));
                        // EnumChildWindows(tmp->GetHWND(), [](HWND hwnd, LPARAM lParam) -> BOOL {
                        //     Panel *pnl = (Panel *)lParam;
                        //     RECT rParent;
                        //     GetWindowRect(pnl->GetHWND(), &rParent);
                        //     printf("%d, %d,%d,%d,%d\n", (int)pnl->GetHWND(),
                        //         rParent.top, rParent.right, rParent.bottom, rParent.left);
                        //
                        //     RECT r;
                        //     GetWindowRect(hwnd, &r);
                        //     printf("%d, %d,%d,%d,%d\n", (int)hwnd,
                        //         r.top, r.right, r.bottom, r.left);
                        //
                        //     int top = r.top - rParent.top;
                        //     int bottom = top+(r.bottom - r.top);
                        //     printf("\t%d %d\n", top, bottom);
                        //
                        //     RECT cRect;
                        //     GetClientRect(pnl->GetHWND(),&cRect);
                        //     pnl->SetSize(cRect.right-cRect.left,bottom);
                        //     return TRUE;
                        // }, (LPARAM)tmp);
                        return TRUE;
                    }
                }
                break;

            }
            break;
        }
        break;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

SettingsWindow *SettingsWindow::Create()
{
    // int x = CW_USEDEFAULT;
    // int y = CW_USEDEFAULT;
    // int w = CW_USEDEFAULT;
    // int h = CW_USEDEFAULT;

    int x = 10;
    int y = 10;
    int w = 400;
    int h = 700;

    SettingsWindow *self = new SettingsWindow();
    if (self && self->WinCreateWindow(0,
        TEXT("SettingsWindow"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // | WS_HSCROLL | WS_VSCROLL,
        x, y, w, h, NULL, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

// void SettingsWindow::RemBorder()
// {
//     m_Borderless = true;
// }
