#ifndef __SETTINGS_WINDOW_H__
#define __SETTINGS_WINDOW_H__

#include <windows.h>
#include <windowsx.h>

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

private:
    HWND m_hWndChild;
    // bool m_Borderless = false;
    ScrollablePanel *m_MainPanel;

    Button *m_TestButton;
    Button *m_TestButton5;

    Button *m_TestButton1;
    Button *m_TestButton2;
    Button *m_TestButton3;
    Button *m_TestButton4;

// public:
//     void RemBorder();
};



#endif // __SETTINGS_WINDOW_H__
