#ifndef __SCROLLABLE_PANEL_H__
#define __SCROLLABLE_PANEL_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include "../common.h"
#include "../base_components/base_panel.h"
#include "panel.h"
#include "scrollbar.h"


class ScrollablePanel : public BasePanel
{
public:
    virtual LPCTSTR ClassName() { return TEXT("ScrollablePanel"); }
    static ScrollablePanel *Create(HWND hWndParent);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    void PaintContent(PAINTSTRUCT *pps);

public:
    bool m_IsVScrollActive;
    int m_VScrollbarWidth;
    Scrollbar *m_VScrollbar;

    // int m_ScrollableContentPanelOffset;
    Panel *m_ScrollableContentPanelBottom;
    Panel *m_ScrollableContentPanel;

public:
    Panel* GetPanel(void);
    void SetVScroll(bool isActive);
    bool IsVScrollActive(void);

private:
    void Update(void);
    // void UpdateScrollBarPosition(void);
    // void UpdateScrollableContentPanelPosition(void);

};



#endif // __SCROLLABLE_PANEL_H__
