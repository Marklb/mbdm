#ifndef __DEBUG_WINDOW_H__
#define __DEBUG_WINDOW_H__

#include <windows.h>
#include <windowsx.h>
#include <vector>

#include "../common.h"
#include "../base_components/base_window.h"
#include "../window_components/panel.h"
#include "../window_components/scrollable_panel.h"
#include "../window_components/button.h"
#include "../utils/paint_utils.h"


class DebugWindow : public BaseWindow
{
public:
    virtual LPCTSTR ClassName() { return TEXT("DebugWindow"); }
    static DebugWindow *Create();

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    int OnResize(WPARAM wParam, LPARAM lParam);

private:
    void InitListPanel(void);
    void UpdateListPanelButtons(void);
    void InitPanels(void);
    void InitPanelWindowsInfo(void);
    void DockConsoleWindow(void);
    void UnDockConsoleWindow(void);

private:
    HWND m_hWndChild;
    int m_DockedConsoleHeight;
    HWND m_hWndDockedConsole;
    HWND m_hWndDockedConsoleOrigParent;
    int m_SelectedPanelIdx;
    ScrollablePanel *m_ListPanel;
    int m_ListPanelBtnsHeight;
    std::vector<Button *> m_ListPanelBtns;
    std::vector<BasePanel *> m_Panels;

};



#endif // __DEBUG_WINDOW_H__
