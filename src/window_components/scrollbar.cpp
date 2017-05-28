#include "scrollbar.h"

LRESULT Scrollbar::OnCreate()
{
    printf("Create scrollbar\n");
    m_BtnsActive = true;
    m_ButtonSize = 10;
    m_Orientation = Scrollbar::ORIENTATION_VERTICAL;
    m_ContentSize = 200;
    m_WindowSize = 100;
    m_GripMinSize = 20;
    m_MoveUnitSize = 10;
    // m_ContentPosition = 100;
    m_ContentPosition = 0;
    m_WindowPanel = NULL;
    m_ContentPanel = NULL;
    m_Timer1Active = false;
    m_Timer2Active = false;
    m_GripPressed = false;
    Update();
    SetBackgroundColor(RGB(50,0,150));
    // ShowWindow(GetHWND(), SW_SHOW);
    return 0;
}

LRESULT Scrollbar::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CREATE:
            return OnCreate();

        case WM_SIZE:
        {
            Update();
        }
        break;

        case WM_TIMER:
        {
            switch (wParam) {
                case Scrollbar::TIMER_1:
                {
                    Decrement();
                }
                break;

                case Scrollbar::TIMER_2:
                {
                    Increment();
                }
                break;
            }
        }
        break;

        case WM_LBUTTONDOWN:
        {
            // printf("\nClicked panel\n");
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
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);
            // printf("Clicked (%d, %d)\n", xPos, yPos);

            RECT b1r;
            GetBtn1Rect(&b1r);
            if(xPos > b1r.left && xPos < b1r.right && yPos > b1r.top
                && yPos < b1r.bottom){
                // printf("Clicked Button 1\n");
                // m_PageOffset-=50;
                // DecrementPageOffset();
                // Decrement();

                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(TRACKMOUSEEVENT);
                tme.dwFlags = TME_LEAVE;
                tme.hwndTrack = GetHWND();
                tme.dwHoverTime = NULL;

                m_Timer1Active = true;
                SetTimer(GetHWND(),Scrollbar::TIMER_1,50,NULL);

                TrackMouseEvent(&tme);
            }

            RECT b2r;
            GetBtn2Rect(&b2r);
            if(xPos > b2r.left && xPos < b2r.right && yPos > b2r.top
                && yPos < b2r.bottom){
                // printf("Clicked Button 2\n");
                // m_PageOffset+=50;
                // IncrementPageOffset();
                // Increment();

                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(TRACKMOUSEEVENT);
                tme.dwFlags = TME_LEAVE;
                tme.hwndTrack = GetHWND();
                tme.dwHoverTime = NULL;

                m_Timer2Active = true;
                SetTimer(GetHWND(),Scrollbar::TIMER_2,50,NULL);

                TrackMouseEvent(&tme);
            }

            RECT gr;
            GetGripRect(&gr);
            if(xPos > gr.left && xPos < gr.right
                && yPos > gr.top && yPos < gr.bottom){
                // printf("Clicked Grip\n");
                m_GripPressed = true;
                if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
                    m_MousePosStart = yPos;
                }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
                    m_MousePosStart = xPos;
                }
                SetCapture(GetHWND());
                // POINT p;
                // p.x = xPos;
                // p.y = yPos;
                // DragDetect(GetHWND(), p);

                RECT r;
                GetClientRect(GetHWND(),&r);
                InvalidateRect(GetHWND(),&r,FALSE);
            }

			break;
		}

        case WM_LBUTTONUP:
        {
            KillTimer(GetHWND(),Scrollbar::TIMER_1);
            m_Timer1Active = false;
            KillTimer(GetHWND(),Scrollbar::TIMER_2);
            m_Timer2Active = false;

            if(m_GripPressed){
                RECT r;
                GetClientRect(GetHWND(),&r);
                InvalidateRect(GetHWND(),&r,FALSE);
            }
            ReleaseCapture();
            m_GripPressed = false;
        }
        break;

        case WM_MOUSELEAVE:
        {
            KillTimer(GetHWND(),Scrollbar::TIMER_1);
            m_Timer1Active = false;
            KillTimer(GetHWND(),Scrollbar::TIMER_2);
            m_Timer2Active = false;
        }
        break;

        case WM_MOUSEMOVE:
        {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);

            // printf("MOVING: %d, %d\n", xPos, yPos);
            if(m_Timer1Active == true){
                RECT b1r;
                GetBtn1Rect(&b1r);
                if(!(xPos > b1r.left && xPos < b1r.right && yPos > b1r.top
                    && yPos < b1r.bottom)){
                    KillTimer(GetHWND(),Scrollbar::TIMER_1);
                    m_Timer1Active = false;
                }
            }

            if(m_Timer2Active == true){
                RECT b2r;
                GetBtn2Rect(&b2r);
                if(!(xPos > b2r.left && xPos < b2r.right && yPos > b2r.top
                    && yPos < b2r.bottom)){
                    KillTimer(GetHWND(),Scrollbar::TIMER_2);
                    m_Timer2Active = false;
                }
            }

            if(m_GripPressed == true){
                // printf("Move Grip: %d, %d\n", xPos, yPos);
                RECT gr;
                GetGripRect(&gr);

                int pos;
                if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
                    pos = yPos;
                }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
                    pos = xPos;
                }
                int mPosDelta = pos - m_MousePosStart;
                // printf("mPosDelta: %d\n", mPosDelta);

                RECT trackRect;
                GetTrackRect(&trackRect);
                float trackSize;
                int trackPos;
                if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
                    // printf("grip(%d, %d)  track(%d, %d)\n", m_GripRect.top, m_GripRect.bottom, trackRect.top, trackRect.bottom);
                    if(m_GripRect.top+mPosDelta < trackRect.top
                        || m_GripRect.bottom+mPosDelta > trackRect.bottom){
                        mPosDelta = 0;
                    }
                    m_GripRect.top += mPosDelta;
                    m_GripRect.bottom += mPosDelta;

                    trackSize = (trackRect.bottom-trackRect.top) - (m_GripRect.bottom-m_GripRect.top);
                    trackPos = m_GripRect.top - trackRect.top;
                }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
                    if(m_GripRect.left+mPosDelta < trackRect.left
                        || m_GripRect.right+mPosDelta > trackRect.right){
                        mPosDelta = 0;
                    }
                    m_GripRect.left += mPosDelta;
                    m_GripRect.right += mPosDelta;

                    trackSize = (trackRect.right-trackRect.left) - (m_GripRect.right-m_GripRect.left);
                    trackPos = m_GripRect.left - trackRect.left;
                }

                m_MousePosStart = pos;

                float windowScrollAreaSize = ((float)GetContentSize())
                    -((float)GetWindowSize());

                // float trackSize = (trackRect.bottom-trackRect.top) - (m_GripRect.bottom-m_GripRect.top);
                // printf("trackSize: %f\n", trackSize);

                // printf("contentPosition: %d\n", GetContentPosition());

                // printf("(%d, %d)\n", gripRect.top, trackRect.top);
                // int trackPos = m_GripRect.top - trackRect.top;
                // printf("trackPos: %d\n", trackPos);

                float ratio = trackPos/trackSize;
                // printf("ratio: %f\n", ratio);

                float newContentPosition = (windowScrollAreaSize * ratio);
                SetContentPosition((int)newContentPosition);
                // Update();

                if(GetContentPanel() != NULL){
                    if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
                        RECT rect;
                        GetClientRect(GetContentPanel()->GetHWND(),&rect);
                        GetContentPanel()->SetPosition(rect.top,-GetContentPosition());
                    }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
                        RECT rect;
                        GetClientRect(GetContentPanel()->GetHWND(),&rect);
                        GetContentPanel()->SetPosition(-GetContentPosition(),rect.left);
                    }
                }

                RECT r;
                GetClientRect(GetHWND(),&r);
                InvalidateRect(GetHWND(),&r,FALSE);
            }
        }
        break;

        case WM_MOUSEWHEEL:
        {
            int incr = 0;
            ((short) HIWORD(wParam)< 0) ? incr-- : incr++;
            // printf("incr: %d\n", incr);
            if(incr > 0){
                Decrement();
            }else if(incr < 0){
                Increment();
            }
        }
        break;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

Scrollbar *Scrollbar::Create(HWND hWndParent)
{
    // printf("Scrollbar::Create scrollbar\n");
    Scrollbar *self = new Scrollbar();
    if (self && self->WinCreateWindow(0,
        TEXT("Scrollbar"), WS_CHILD | WS_CLIPCHILDREN,
        20, 20, 200, 200, hWndParent, NULL)) {
        return self;
    }
    delete self;
    return NULL;
}

void Scrollbar::PaintContent(PAINTSTRUCT *pps)
{
    // return;
    // HDC hdc = GetDC(GetHWND());
    HDC hdc = pps->hdc;
    // printf("hdc: %d\n", (int)(&hdc));
    // printf("hdc2: %d\n", (int)(&(pps->hdc)));

    // printf("%d,%d,%d,%d\n", pps->rcPaint);

    RECT clientRect;
    GetClientRect(GetHWND(),&clientRect);

    // int width = clientRect.right - clientRect.left;
    // int height = clientRect.bottom - clientRect.top;

    // HDC bufDC;
    // HBITMAP bufBMP;

    // bufDC = CreateCompatibleDC(hdc);
    // bufBMP = CreateCompatibleBitmap(hdc, width, height);
    // SelectObject(bufDC, bufBMP);

    // RECT rect;
    // GetClientRect(hWnd, &rect);
    

    RECT b1r;
    GetBtn1Rect(&b1r);

    RECT b2r;
    GetBtn2Rect(&b2r);

    RECT gr;
    GetGripRect(&gr);

    HBRUSH hBrushBtn = CreateSolidBrush(RGB(0,0,0));
    HBRUSH hBrushGrip = CreateSolidBrush(RGB(0,150,0));
    // if(m_GripPressed == true){
    //     hBrushGrip = CreateSolidBrush(RGB(40,60,120));
    // }


    // FillRect(hdc,&b1r,hBrushBtn);
    // FillRect(hdc,&b2r,hBrushBtn);
    // FillRect(hdc,&gr,hBrushGrip);

    HBRUSH hBrushBg = CreateSolidBrush(m_BgColor);
    FillRect(hdc,&clientRect,hBrushBg);

    FillRect(hdc,&b1r,hBrushBtn);
    FillRect(hdc,&b2r,hBrushBtn);
    FillRect(hdc,&gr,hBrushGrip);

    // BitBlt(hdc, 0, 0, width, height, bufDC, 0, 0, SRCCOPY);

    // ReleaseDC(GetHWND(),hdc);
    DeleteObject(hBrushBtn);
    DeleteObject(hBrushGrip);
    DeleteObject(hBrushBg);
    // DeleteObject(bufBMP);
    // DeleteDC(bufDC);
    // ReleaseDC(GetHWND(),bufDC);
}

void Scrollbar::SetButtonsActive(bool b)
{
    m_BtnsActive = b;
}

bool Scrollbar::IsButtonsActive(void)
{
    return m_BtnsActive;
}

void Scrollbar::SetButtonSize(int size)
{
    m_ButtonSize = size;
}

int Scrollbar::GetButtonSize(void)
{
    return m_ButtonSize;
}

void Scrollbar::SetOrientation(short o)
{
    m_Orientation = o;
}

short Scrollbar::GetOrientation(void)
{
    return m_Orientation;
}

void Scrollbar::SetContentSize(int size)
{
    m_ContentSize = size;
}

int Scrollbar::GetContentSize(void)
{
    return m_ContentSize;
}

void Scrollbar::SetWindowSize(int size)
{
    m_WindowSize = size;
}

int Scrollbar::GetWindowSize(void)
{
    return m_WindowSize;
}

void Scrollbar::SetGripMinSize(int size)
{
    m_GripMinSize = size;
}

int Scrollbar::GetGripMinSize(void)
{
    return m_GripMinSize;
}

void Scrollbar::SetMoveUnitSize(int size)
{
    m_MoveUnitSize = size;
}

int Scrollbar::GetMoveUnitSize(void)
{
    return m_MoveUnitSize;
}

void Scrollbar::SetContentPosition(int pos)
{
    m_ContentPosition = pos;
}

int Scrollbar::GetContentPosition(void)
{
    return m_ContentPosition;
}

void Scrollbar::GetBtn1Rect(RECT *r)
{
    r->top = m_Btn1Rect.top;
    r->right = m_Btn1Rect.right;
    r->bottom = m_Btn1Rect.bottom;
    r->left = m_Btn1Rect.left;
}

void Scrollbar::GetBtn2Rect(RECT *r)
{
    r->top = m_Btn2Rect.top;
    r->right = m_Btn2Rect.right;
    r->bottom = m_Btn2Rect.bottom;
    r->left = m_Btn2Rect.left;
}

void Scrollbar::GetGripRect(RECT *r)
{
    r->top = m_GripRect.top;
    r->right = m_GripRect.right;
    r->bottom = m_GripRect.bottom;
    r->left = m_GripRect.left;
}

void Scrollbar::GetTrackRect(RECT *r)
{
    RECT clientRect;
    GetClientRect(GetHWND(),&clientRect);
    if(IsButtonsActive()){
        RECT b1r;
        GetBtn1Rect(&b1r);

        RECT b2r;
        GetBtn2Rect(&b2r);

        if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
            r->top = b1r.bottom;
            r->right = clientRect.right;
            r->bottom = b2r.top;
            r->left = clientRect.left;
        }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
            r->top = clientRect.top;
            r->right = b2r.left;
            r->bottom = clientRect.bottom;
            r->left = b1r.right;
        }
    }else{
        r->top = clientRect.top;
        r->right = clientRect.right;
        r->bottom = clientRect.bottom;
        r->left = clientRect.left;
    }
}

void Scrollbar::SetContentPanel(BasePanel *panel)
{
    m_ContentPanel = panel;
}

BasePanel* Scrollbar::GetContentPanel(void)
{
    return m_ContentPanel;
}

void Scrollbar::SetWindowPanel(BasePanel *panel)
{
    m_WindowPanel = panel;
}

BasePanel* Scrollbar::GetWindowPanel(void)
{
    return m_WindowPanel;
}

void Scrollbar::Increment(void)
{
    int newContentPos = GetContentPosition() + GetMoveUnitSize();
    float windowScrollAreaSize = ((float)GetContentSize())
        -((float)GetWindowSize());
    if(newContentPos > windowScrollAreaSize){
        newContentPos = windowScrollAreaSize;
    }
    // printf("newContentPos: %d\n",newContentPos);
    SetContentPosition(newContentPos);
    Update();
}

void Scrollbar::Decrement(void)
{
    int newContentPos = GetContentPosition() - GetMoveUnitSize();
    if(newContentPos < 0){
        newContentPos = 0;
    }
    // printf("newContentPos: %d\n",newContentPos);
    SetContentPosition(newContentPos);
    Update();
}

// void Scrollbar::UpdateContentPanelPosition(void)
// {
//     if(GetContentPanel() != NULL){
//         if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
//             RECT rect;
//             GetClientRect(GetContentPanel()->GetHWND(),&rect);
//             GetContentPanel()->SetPosition(GetContentPosition(),rect.left);
//         }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
//             RECT rect;
//             GetClientRect(GetContentPanel()->GetHWND(),&rect);
//             GetContentPanel()->SetPosition(rect.top,GetContentPosition());
//         }
//     }
// }

void Scrollbar::Update(void)
{
    // printf("\nScrollbar::Update\n");
    RECT clientRect;
    GetClientRect(GetHWND(),&clientRect);

    // printf("clientRect: top: %d, right: %d, bottom: %d, left: %d\n",
    //     clientRect.top, clientRect.right, clientRect.bottom, clientRect.left);

    float trackSize;

    // Update Buttons Rects
    if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
        m_Btn1Rect.top = clientRect.top;
        m_Btn1Rect.right = clientRect.right;
        m_Btn1Rect.bottom = clientRect.top + GetButtonSize();
        m_Btn1Rect.left = clientRect.left;

        m_Btn2Rect.top = clientRect.bottom - GetButtonSize();
        m_Btn2Rect.right = clientRect.right;
        m_Btn2Rect.bottom = clientRect.bottom;
        m_Btn2Rect.left = clientRect.left;

        if(!IsButtonsActive()){
            // printf("ButtonActive: false\n");
            trackSize = clientRect.bottom - clientRect.top;
        }else{
            // printf("ButtonActive: true\n");
            trackSize = m_Btn2Rect.top - m_Btn1Rect.bottom;
        }
    }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
        m_Btn1Rect.top = clientRect.top;
        m_Btn1Rect.right = clientRect.left + GetButtonSize();
        m_Btn1Rect.bottom = clientRect.bottom;
        m_Btn1Rect.left = clientRect.left;

        m_Btn2Rect.top = clientRect.top;
        m_Btn2Rect.right = clientRect.right;
        m_Btn2Rect.bottom = clientRect.bottom;
        m_Btn2Rect.left = clientRect.right - GetButtonSize();

        if(!IsButtonsActive()){
            trackSize = clientRect.right - clientRect.left;
        }else{
            trackSize = m_Btn2Rect.left - m_Btn1Rect.right;
        }
    }

    // printf("trackSize: %f\n", trackSize);

    // printf("m_Btn1Rect: top: %d, right: %d, bottom: %d, left: %d\n",
    //     m_Btn1Rect.top, m_Btn1Rect.right, m_Btn1Rect.bottom, m_Btn1Rect.left);
    // printf("m_Btn2Rect: top: %d, right: %d, bottom: %d, left: %d\n",
    //     m_Btn2Rect.top, m_Btn2Rect.right, m_Btn2Rect.bottom, m_Btn2Rect.left);

    // printf("GetWindowSize: %d\n", GetWindowSize());
    // printf("GetContentSize: %d\n", GetContentSize());

    // Calculate new positions
    float windowContentRatio = ((float)GetWindowSize())
        /((float)GetContentSize());

    // printf("windowContentRatio: %f\n", windowContentRatio);

    float gripSize = trackSize * windowContentRatio;
    if(gripSize < GetGripMinSize()) gripSize = (float)GetGripMinSize();
    if(gripSize > trackSize) gripSize = trackSize;

    // printf("gripSize: %f\n", gripSize);

    float windowScrollAreaSize = ((float)GetContentSize())
        -((float)GetWindowSize());

    // printf("windowScrollAreaSize: %f\n", windowScrollAreaSize);

    float windowPositionRatio = 0.0;

    if(windowScrollAreaSize > 0.00000001 || windowScrollAreaSize < -0.00000001){
        windowPositionRatio = ((float)GetContentPosition())
            /windowScrollAreaSize;
        // printf("windowPositionRatio: (%f,/%f): %f\n", (float)GetContentPosition(),
        //     windowScrollAreaSize, windowPositionRatio);
    }

    // printf("windowPositionRatio: %f\n", windowPositionRatio);

    float trackScrollAreaSize = trackSize - gripSize;

    // printf("trackScrollAreaSize: %f\n", trackScrollAreaSize);

    float gripPositionOnTrack = trackScrollAreaSize * windowPositionRatio;

    // printf("gripPositionOnTrack: %f\n", gripPositionOnTrack);

    // Update Grip Rect
    if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
        m_GripRect.top = gripPositionOnTrack;
        m_GripRect.right = clientRect.right;
        m_GripRect.bottom = gripPositionOnTrack + gripSize;
        m_GripRect.left = clientRect.left;
        if(IsButtonsActive()){
            m_GripRect.top += m_Btn1Rect.bottom;
            m_GripRect.bottom += m_Btn1Rect.bottom;
        }
    }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
        m_GripRect.top = clientRect.top;
        m_GripRect.right = gripPositionOnTrack + gripSize;
        m_GripRect.bottom = clientRect.bottom;
        m_GripRect.left = gripPositionOnTrack;
        if(IsButtonsActive()){
            m_GripRect.right += m_Btn1Rect.right;
            m_GripRect.left += m_Btn1Rect.right;
        }
    }
    // printf("m_GripRect: top: %d, right: %d, bottom: %d, left: %d\n",
    //     m_GripRect.top, m_GripRect.right, m_GripRect.bottom, m_GripRect.left);

    // float newContentPosition = gripPositionOnTrack/trackScrollAreaSize;
    // SetContentPosition((int)newContentPosition);
    if(GetContentPanel() != NULL){
        if(GetOrientation() == Scrollbar::ORIENTATION_VERTICAL){
            RECT rect;
            GetClientRect(GetContentPanel()->GetHWND(),&rect);
            GetContentPanel()->SetPosition(rect.top,-GetContentPosition());
        }else if(GetOrientation() == Scrollbar::ORIENTATION_HORIZONTAL){
            RECT rect;
            GetClientRect(GetContentPanel()->GetHWND(),&rect);
            GetContentPanel()->SetPosition(-GetContentPosition(),rect.left);
        }
    }

    RECT r;
    GetClientRect(GetHWND(),&r);
    InvalidateRect(GetHWND(),&r,FALSE);
}
