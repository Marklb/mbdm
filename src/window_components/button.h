#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include "../common.h"
#include "../base_components/base_panel.h"


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

public:
    void SetText(char *text);
    void SetButtonTextColor(COLORREF color);

};



#endif // __BUTTON_H__
