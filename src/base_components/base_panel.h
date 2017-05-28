#ifndef __BASE_PANEL_H__
#define __BASE_PANEL_H__

#include <windows.h>

#include "../common.h"
#include "../utils/paint_utils.h"

class BasePanel
{
protected:
    HWND m_hWnd;
    COLORREF m_BgColor = COLOR_NONE;

protected:
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void PaintContent(PAINTSTRUCT *pps) { }
    virtual LPCTSTR ClassName() = 0;
    virtual BOOL WinRegisterClass(WNDCLASS *pwc) { return RegisterClass(pwc); }
    virtual ~BasePanel() { }

    HWND WinCreateWindow(DWORD dwExStyle, LPCTSTR pszName, DWORD dwStyle,
        int x, int y, int cx, int cy, HWND hWndParent, HMENU hMenu)
    {
        Register();
        return CreateWindowEx(dwExStyle,  ClassName(), pszName, dwStyle,
            x, y, cx, cy, hWndParent, hMenu, g_hInst, this);
    }

public:
    HWND GetHWND() { return m_hWnd; }


private:
    void Register();
    void OnPaint();
    void OnPrintClient(HDC hdc);
    void PaintBackground(PAINTSTRUCT *pps);
    static LRESULT CALLBACK s_WndProc(HWND hWnd,
        UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    void SetPosition(int x, int y);
    void SetSize(int w, int h);
    void SetBackgroundColor(COLORREF color);
};



#endif // __BASE_PANEL_H__
