#include "debug_window.h"

LRESULT DebugWindow::OnCreate()
{
    m_DockedConsoleHeight = 200;
    m_ListPanelBtnsHeight = 40;
    m_SelectedPanelIdx = 0;
    this->InitListPanel();
    this->DockConsoleWindow();
    this->InitPanels();

    return 0;
}

LRESULT DebugWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
                    // SendMessage(m_ListPanel->GetHWND(),
                        // WM_NOTIFY,
                        // kbnmh.nmh.idFrom,
                        // (LPARAM)&kbnmh);
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
                    // if (((LPNMHDR)lParam)->hwndFrom == m_TestButton->GetHWND()){
                    //     printf("Toggle\n");
                    //     m_MainPanel->SetVScroll(!m_MainPanel->IsVScrollActive());
                    //     return TRUE;
                    // }
                }
                break;

            }
            break;
        }
        break;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

DebugWindow *DebugWindow::Create()
{
    // int x = CW_USEDEFAULT;
    // int y = CW_USEDEFAULT;
    // int w = CW_USEDEFAULT;
    // int h = CW_USEDEFAULT;

    int x = 10;
    int y = 10;
    int w = 400;
    int h = 700;

    DebugWindow *self = new DebugWindow();
    if (self && self->WinCreateWindow(0,
        TEXT("DebugWindow"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // | WS_HSCROLL | WS_VSCROLL,
        x, y, w, h, NULL, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

// ----------------------------------------------------------------------------
// Called on WM_SIZE
// ----------------------------------------------------------------------------
int DebugWindow::OnResize(WPARAM wParam, LPARAM lParam)
{
    if (m_hWndChild) {
        SetWindowPos(m_hWndChild, NULL, 0, 0,
                        GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),
                        SWP_NOZORDER | SWP_NOACTIVATE);
    }

    RECT clientRect;
    RECT listPanelRect;
    RECT consoleRect;
    int x,y,w,h;

    GetClientRect(this->GetHWND(), &clientRect);

    if(m_ListPanel){
        m_ListPanel->SetPosition(0,0);
        GetClientRect(m_ListPanel->GetHWND(), &listPanelRect);
        m_ListPanel->SetSize(
            listPanelRect.right - listPanelRect.left,
            clientRect.bottom - clientRect.top);
        GetClientRect(m_ListPanel->GetHWND(), &listPanelRect);
    }

    if(m_hWndDockedConsole){
        GetClientRect(m_hWndDockedConsole, &consoleRect);
        x = listPanelRect.right;
        y = clientRect.bottom - m_DockedConsoleHeight;
        w = clientRect.right - listPanelRect.right;
        h = m_DockedConsoleHeight;
        SetWindowPos(m_hWndDockedConsole,NULL,x,y,w,h,SWP_NOACTIVATE 
            | SWP_NOOWNERZORDER | SWP_NOZORDER);
    }

    this->UpdateListPanelButtons();


    

    return 0;
}

void DebugWindow::InitListPanel(void)
{
    m_ListPanel = ScrollablePanel::Create(GetHWND());
    m_ListPanel->SetPosition(0,0);
    m_ListPanel->SetSize(300,500);
    m_ListPanel->GetPanel()->SetBackgroundColor(RGB(30,0,80));
    // m_ListPanel->SetBackgroundColor(RGB(0,0,0));
    m_ListPanel->SetVScroll(true);
    ShowWindow(m_ListPanel->GetHWND(),SW_SHOW);
}

void DebugWindow::UpdateListPanelButtons(void)
{
    // for(int i = 0; i < m_ListPanelBtns.Size(); i++){
        // Button *btn 

    RECT clientRect;
    RECT sbRect;
    // GetClientRect(m_ListPanel->GetPanel()->GetHWND(), &clientRect);
    GetClientRect(m_ListPanel->GetHWND(), &clientRect);
    GetClientRect(m_ListPanel->GetVScrollBar()->GetHWND(), &sbRect);

    int btnsAdded = 0;
    for(Button *btn : m_ListPanelBtns){
        if(IsWindowVisible(btn->GetHWND())){
            btn->SetPosition(0,btnsAdded*m_ListPanelBtnsHeight);
            btn->SetSize((clientRect.right - clientRect.left) 
                - (sbRect.right - sbRect.left),
                m_ListPanelBtnsHeight);
            btnsAdded++;
        }
    }

    int count = 0;
    for(BasePanel *panel : m_Panels){
        if(count == m_SelectedPanelIdx){
            if(!IsWindowVisible(panel->GetHWND())){
                ShowWindow(panel->GetHWND(), SW_SHOW);
                
            }
            int x,y,w,h;
            RECT rect;
            RECT listRect;
            RECT consoleRect;
            GetClientRect(this->GetHWND(), &rect);
            GetClientRect(m_ListPanel->GetHWND(), &listRect);
            x = listRect.right;
            y = 0;
            w = rect.right - x;
            if(m_hWndDockedConsole){
                GetClientRect(m_hWndDockedConsole, &consoleRect);
                h = rect.bottom - (consoleRect.bottom - consoleRect.top) - y;
            }else{
                h = rect.bottom - y;
            }
            panel->SetPosition(x, y);
            panel->SetSize(w, h);
        }else{
            if(IsWindowVisible(panel->GetHWND())){
                ShowWindow(panel->GetHWND(), SW_HIDE);
            }
        }
        count++;
    }
}

void DebugWindow::InitPanels(void)
{
    this->InitPanelWindowsInfo();
}

void DebugWindow::InitPanelWindowsInfo(void)
{
    // Add a list item
    Button *listBtn = Button::Create(m_ListPanel->GetPanel()->GetHWND());
    // m_TestButton1->SetPosition(0,0);
    // m_TestButton1->SetSize(300,50);
    listBtn->SetText("Windows Info");
    ShowWindow(listBtn->GetHWND(), SW_SHOW);
    m_ListPanelBtns.push_back(listBtn);

    Button *listBtn2 = Button::Create(m_ListPanel->GetPanel()->GetHWND());
    listBtn2->SetText("Keyboard");
    ShowWindow(listBtn2->GetHWND(), SW_SHOW);
    m_ListPanelBtns.push_back(listBtn2);

    // Build the panel
    ScrollablePanel *panel = ScrollablePanel::Create(this->GetHWND());
    panel->GetPanel()->SetBackgroundColor(RGB(10,0,10));
    panel->GetPanel()->SetSize(3000,2000);
    panel->SetVScroll(true);
    m_Panels.push_back(panel);
}


void DebugWindow::DockConsoleWindow(void)
{
    // Attach the command prompt window by setting this window as the parent
    m_hWndDockedConsole = GetConsoleWindow();
    m_hWndDockedConsoleOrigParent = SetParent(m_hWndDockedConsole, 
        this->GetHWND());

    // Remove the borders and caption
    SetWindowLong(m_hWndDockedConsole, GWL_STYLE, 
        GetWindowLong(m_hWndDockedConsole, GWL_STYLE) 
        & ~(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME));
    SetWindowLong(m_hWndDockedConsole, GWL_EXSTYLE,
        GetWindowLong(m_hWndDockedConsole, GWL_EXSTYLE) & ~WS_EX_DLGMODALFRAME);
}

void DebugWindow::UnDockConsoleWindow(void)
{
    SetParent(m_hWndDockedConsole, m_hWndDockedConsoleOrigParent);

    // TODO: Restore styles

    m_hWndDockedConsole = NULL;
}
