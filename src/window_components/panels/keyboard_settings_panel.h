#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include "../../common.h"
#include "../../base_components/base_panel.h"

class KeyboardSettingsPanel : public BasePanel
{
public:
    virtual LPCTSTR ClassName() { return TEXT("KeyboardSettingsPanel"); }
    static KeyboardSettingsPanel *Create(HWND hWndParent);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    void PaintContent(PAINTSTRUCT *pps);

};



#endif // __BUTTON_H__
