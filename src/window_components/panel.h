#ifndef __PANEL_H__
#define __PANEL_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include "../common.h"
#include "../base_components/base_panel.h"
#include "scrollbar.h"


class Panel : public BasePanel
{
public:
    virtual LPCTSTR ClassName() { return TEXT("Panel"); }
    static Panel *Create(HWND hWndParent);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    void PaintContent(PAINTSTRUCT *pps);

};



#endif // __PANEL_H__
