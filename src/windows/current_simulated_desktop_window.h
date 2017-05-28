#ifndef __CURRENT_SIMULATED_DESKTOP_WINDOW_H__
#define __CURRENT_SIMULATED_DESKTOP_WINDOW_H__

#include <windows.h>
#include <windowsx.h>

#include "../common.h"
#include "../base_components/base_window.h"
#include "../window_components/panel.h"
#include "../window_components/scrollable_panel.h"
#include "../window_components/button.h"
#include "../utils/paint_utils.h"

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms633556(v=vs.85).aspx

class CurrentSimulatedDesktopWindow : public BaseWindow
{
public:
    virtual LPCTSTR ClassName() { return TEXT("CurrentSimulatedDesktopWindow"); }
    static CurrentSimulatedDesktopWindow *Create();

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    virtual void PaintContent(PAINTSTRUCT *pps);

public:
    std::string m_Text;
    
public:
    void SetText(char *text);

};



#endif // __CURRENT_SIMULATED_DESKTOP_WINDOW_H__
