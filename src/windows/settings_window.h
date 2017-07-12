#ifndef __SETTINGS_WINDOW_H__
#define __SETTINGS_WINDOW_H__

#include <windows.h>
#include <windowsx.h>
#include <vector>

#include "../common.h"
#include "../base_components/base_window.h"
#include "../window_components/panel.h"
#include "../window_components/scrollable_panel.h"
#include "../window_components/button.h"
#include "../utils/paint_utils.h"


class SettingsWindow : public BaseWindow
{
public:
    virtual LPCTSTR ClassName() { return TEXT("SettingsWindow"); }
    static SettingsWindow *Create();

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();

public:
    int OnResize(WPARAM wParam, LPARAM lParam);
    void InitSidePanel(void);
    void UpdateSidePanelButtons(void);
    void InitPanels(void);
    void InitPanelWindowsInfo(void);

private:
    int OnMouseDownTest(HWND hWnd, WPARAM wParam, LPARAM lParam);
    int OnMouseDownKeyboard(HWND hWnd, WPARAM wParam, LPARAM lParam);
    int ListenedMessage(BasePanel *from, UINT uMsg, WPARAM wParam, 
        LPARAM lParam);

private:
    HWND m_hWndChild;
    // bool m_Borderless = false;
    ScrollablePanel *m_SidePanel;

    int m_SelectedPanelIdx;
    int m_SidePanelBtnsHeight;
    std::vector<Button *> m_SidePanelBtns;
    std::vector<BasePanel *> m_Panels;

    // Button *m_TestButton;
    // Button *m_TestButton5;

    // Button *m_TestButton1;
    // Button *m_TestButton2;
    // Button *m_TestButton3;
    // Button *m_TestButton4;

// public:
//     void RemBorder();
};



#endif // __SETTINGS_WINDOW_H__
