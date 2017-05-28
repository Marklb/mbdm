#include "scrollbar.h"

LRESULT Scrollbar::OnCreate()
{
    printf("Create scrollbar\n");
    m_PageHeight = 0;
    m_PageOffset = 0;
    m_OffsetIncrement = 50;
    SetBackgroundColor(RGB(50,0,150));
    ShowWindow(GetHWND(), SW_SHOW);
    return 0;
}

LRESULT Scrollbar::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CREATE:
            return OnCreate();

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
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);
            // printf("Clicked (%d, %d)\n", xPos, yPos);

            RECT tb;
            GetTopButtonRect(&tb);
            if(xPos > tb.left && xPos < tb.right && yPos > tb.top
                && yPos < tb.bottom){
                printf("Clicked Top Button\n");
                // m_PageOffset-=50;
                DecrementPageOffset();
            }

            RECT bb;
            GetBottomButtonRect(&bb);
            if(xPos > bb.left && xPos < bb.right && yPos > bb.top
                && yPos < bb.bottom){
                printf("Clicked Bottom Button\n");
                // m_PageOffset+=50;
                IncrementPageOffset();
            }

            RECT thumbRect;
            GetThumbRect(&thumbRect);
            if(xPos > thumbRect.left && xPos < thumbRect.right
                && yPos > thumbRect.top && yPos < thumbRect.bottom){
                printf("Clicked Thumb Button\n");
            }

			break;
		}
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

Scrollbar *Scrollbar::Create(HWND hWndParent)
{
    printf("Scrollbar::Create scrollbar\n");
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
    HDC hdc = GetDC(GetHWND());

    // RECT rect;
    // GetClientRect(hWnd, &rect);

    RECT topBtnRect;
    GetTopButtonRect(&topBtnRect);

    RECT bottomBtnRect;
    GetBottomButtonRect(&bottomBtnRect);

    RECT thumbRect;
    GetThumbRect(&thumbRect);

    HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));
    HBRUSH hBrushThumb = CreateSolidBrush(RGB(0,150,0));



    FillRect(hdc,&topBtnRect,hBrush);
    FillRect(hdc,&bottomBtnRect,hBrush);
    FillRect(hdc,&thumbRect,hBrushThumb);

    // ReleaseDC(hWnd,hdc);
    DeleteObject(hBrush);
    DeleteObject(hBrushThumb);
}

// void Scrollbar::SetClientHeight(int h)
// {
//     m_ClientHeight = h;
// }

void Scrollbar::SetPageHeight(int h)
{
    m_PageHeight = h;
}

int Scrollbar::GetPageOffset(void)
{
    return m_PageOffset;
}

void Scrollbar::SetPageOffset(int y)
{
    m_PageOffset = y;
    if(m_PageOffset < 0){
        m_PageOffset = 0;
    }

    RECT thumbRect;
    GetThumbRect(&thumbRect);
    int thumbHeight = thumbRect.bottom-thumbRect.top;

    RECT tb;
    GetTopButtonRect(&tb);

    RECT bb;
    GetBottomButtonRect(&bb);
    printf("PageOffset: %d\n", m_PageOffset);
    if(thumbRect.bottom > bb.top){
        // m_PageOffset -= thumbRect.bottom-bb.top;
        RECT rect;
        GetClientRect(GetHWND(), &rect);

        int h = (rect.bottom-rect.top)
            -(tb.bottom-tb.top)
            -(bb.bottom-bb.top);

        int t = h-thumbHeight;
        int npo = t*(m_PageHeight/h);
        printf("NPE: %d\n",npo);
        m_PageOffset = npo;

    }



    RECT tmpRect;
    GetClientRect(GetHWND(),&tmpRect);
    InvalidateRect(GetHWND(),&tmpRect,FALSE);
    NMHDR nmh;
    // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
    nmh.code = SBMSG_OFFSET_CHANGE;    // Message type defined by control.
    nmh.idFrom = GetDlgCtrlID(GetHWND());
    nmh.hwndFrom = GetHWND();
    SendMessage(GetParent(GetHWND()),
        WM_NOTIFY,
        nmh.idFrom,
        (LPARAM)&nmh);
}

void Scrollbar::IncrementPageOffset(void)
{
    SetPageOffset(GetPageOffset()+m_OffsetIncrement);
}

void Scrollbar::DecrementPageOffset(void)
{
    SetPageOffset(GetPageOffset()-m_OffsetIncrement);
}

void Scrollbar::GetTopButtonRect(RECT *r)
{
    RECT rect;
    GetClientRect(GetHWND(), &rect);

    r->top = rect.top;
    r->right = rect.right - rect.left;
    r->bottom = rect.right-rect.left;
    r->left = rect.left;
}

void Scrollbar::GetBottomButtonRect(RECT *r)
{
    RECT rect;
    GetClientRect(GetHWND(), &rect);

    r->top = rect.bottom - (rect.right-rect.left);
    r->right = rect.right - rect.left;
    r->bottom = rect.bottom;
    r->left = rect.left;
}

void Scrollbar::GetThumbRect(RECT *r)
{
    RECT tb;
    GetTopButtonRect(&tb);
    RECT bb;
    GetBottomButtonRect(&bb);

    RECT rect;
    GetClientRect(GetHWND(), &rect);

    int h = (rect.bottom-rect.top)
        -(tb.bottom-tb.top)
        -(bb.bottom-bb.top);

    // float thumbHeight = ceil( (h/m_PageHeight)*h );
    // float thumbHeight = ( (h/m_PageHeight)*h );
    float thumbHeight = ceil( (h/((float)m_PageHeight))*h );
    // float thumbOffset = ceil( (h/((float)m_PageHeight))* );

    printf("tb(%d,%d), bb(%d,%d)  %d\n", tb.top, tb.bottom, bb.top, bb.bottom, bb.top-tb.bottom);
    printf("m_PageHeight: %d\n", m_PageHeight);
    printf("h: %d, thumbHeight: %f\n", h, thumbHeight);
    // int relativeDist = ceil(m_PageOffset*(h/((float)m_PageHeight)));
    printf("PageOffset: %d\n", m_PageOffset);
    int relativeDist = GetRelativeHorizontalDistance(m_PageOffset);
    printf("relativeDist: %d\n", relativeDist);

    // r->top = tb.bottom+m_PageOffset;
    // r->right = rect.right-rect.left;
    // r->bottom = r->top+thumbHeight;
    // r->left = rect.left;

    r->top = tb.bottom+relativeDist;
    r->right = rect.right-rect.left-2;
    r->bottom = r->top+thumbHeight;
    r->left = rect.left+2;
}

int Scrollbar::GetRelativeHorizontalDistance(int d)
{
    RECT tb;
    GetTopButtonRect(&tb);
    RECT bb;
    GetBottomButtonRect(&bb);

    RECT rect;
    GetClientRect(GetHWND(), &rect);

    int h = (rect.bottom-rect.top)
        -(tb.bottom-tb.top)
        -(bb.bottom-bb.top);
    printf("--h: %d\n",h);

    return ceil(d*(h/((float)m_PageHeight)));
}
