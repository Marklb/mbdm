#ifndef __SCROLLBAR_H__
#define __SCROLLBAR_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <math.h>

#include "../common.h"
#include "../base_components/base_panel.h"

// http://csdgn.org/inform/scrollbar-mechanics
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms645533(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms646256(v=vs.85).aspx


#define SBMSG_OFFSET_CHANGE 1

class Scrollbar : public BasePanel
{
public:
    const static short ORIENTATION_VERTICAL = 0;
    const static short ORIENTATION_HORIZONTAL = 1;

    const static unsigned short TIMER_1 = 1;
    const static unsigned short TIMER_2 = 2;

public:
    virtual LPCTSTR ClassName() { return TEXT("mb_Scrollbar"); }
    static Scrollbar *Create(HWND hWndParent);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    void PaintContent(PAINTSTRUCT *pps);

private:
    bool m_BtnsActive;
    int m_ButtonSize;
    short m_Orientation;
    int m_ContentSize;
    int m_WindowSize;
    int m_GripMinSize;
    int m_MoveUnitSize;
    int m_ContentPosition;
    RECT m_Btn1Rect;
    RECT m_Btn2Rect;
    RECT m_GripRect;
    BasePanel *m_WindowPanel;
    BasePanel *m_ContentPanel;
    bool m_Timer1Active;
    bool m_Timer2Active;
    bool m_GripPressed;
    int m_MousePosStart;

public:
    void SetButtonsActive(bool b);
    bool IsButtonsActive(void);
    void SetButtonSize(int size);
    int GetButtonSize(void);
    void SetOrientation(short o);
    short GetOrientation(void);
    void SetContentSize(int size);
    int GetContentSize(void);
    void SetWindowSize(int size);
    int GetWindowSize(void);
    void SetGripMinSize(int size);
    int GetGripMinSize(void);
    void SetMoveUnitSize(int size);
    int GetMoveUnitSize(void);
    void SetContentPosition(int size);
    int GetContentPosition(void);
    void GetBtn1Rect(RECT *r);
    void GetBtn2Rect(RECT *r);
    void GetGripRect(RECT *r);
    void GetTrackRect(RECT *r);
    void SetContentPanel(BasePanel *panel);
    BasePanel* GetContentPanel(void);
    void SetWindowPanel(BasePanel *panel);
    BasePanel* GetWindowPanel(void);
    void Increment(void);
    void Decrement(void);
    // void UpdateContentPanelPosition(void);
    void Update(void);



};



#endif // __SCROLLBAR_H__
