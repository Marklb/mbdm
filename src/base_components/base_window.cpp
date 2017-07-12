#include "base_window.h"





void BaseWindow::Register()
{
    WNDCLASS wc;
    wc.style         = 0;
    wc.lpfnWndProc   = BaseWindow::s_WndProc;
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

LRESULT CALLBACK BaseWindow::s_WndProc(HWND hWnd,
    UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BaseWindow *self;
    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        self = reinterpret_cast<BaseWindow *>(lpcs->lpCreateParams);
        self->m_hWnd = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(self));
    } else {
        self = reinterpret_cast<BaseWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }
    if (self) {
        return self->HandleMessage(uMsg, wParam, lParam);
    } else {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

LRESULT BaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

        case WM_NCCALCSIZE:
        {
			// this kills the window frame and title bar we added with
			// WS_THICKFRAME or WS_CAPTION
			if (m_Borderless) return 0;
			break;
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
        //   return (LRESULT)1; // Say we handled it.

        case WM_SIZE: return this->OnResize(wParam, lParam);
    }

    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void BaseWindow::OnPaint()
{
    PAINTSTRUCT ps;
    BeginPaint(m_hWnd, &ps);
    PaintContent(&ps);
    EndPaint(m_hWnd, &ps);
}

void BaseWindow::OnPrintClient(HDC hdc)
{
    PAINTSTRUCT ps;
    ps.hdc = hdc;
    GetClientRect(m_hWnd, &ps.rcPaint);
    PaintContent(&ps);
}

int BaseWindow::OnResize(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void BaseWindow::SetPosition(int x, int y)
{
    SetWindowPos(GetHWND(),NULL,x,y,NULL,NULL,SWP_NOACTIVATE | SWP_NOSIZE
        | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void BaseWindow::SetSize(int w, int h)
{
    SetWindowPos(GetHWND(),NULL,NULL,NULL,w,h,SWP_NOACTIVATE | SWP_NOMOVE
        | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void BaseWindow::EnableBorder(bool b)
{
    m_Borderless = !b;
}
