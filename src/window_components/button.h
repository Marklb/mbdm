#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include "../common.h"
#include "../base_components/base_panel.h"

// class Button;

// typedef int (Button::*BUTTON_MSG_FN)(HWND hWnd, WPARAM wParam, LPARAM lParam);

class Button : public BasePanel
{
public:
    virtual LPCTSTR ClassName() { return TEXT("mb_Button"); }
    static Button *Create(HWND hWndParent);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    void PaintContent(PAINTSTRUCT *pps);

public:
    std::string m_Text;
    COLORREF m_TextColor;
    // BUTTON_MSG_FN m_OnMouseDownFn;

public:
    void SetText(char *text);
    void SetButtonTextColor(COLORREF color);
    // void SetOnMouseDownFn(BUTTON_MSG_FN fn);
};



#endif // __BUTTON_H__
