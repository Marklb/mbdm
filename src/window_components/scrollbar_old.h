#ifndef __SCROLLBAR_H__
#define __SCROLLBAR_H__

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <math.h>

#include "../common.h"
#include "../base_components/base_panel.h"

//                       __
//    Scroll arrow (up) |  |
//                      |--| <-- m_nMin
//                      |  |
//                      |  |
//                      |==|-. <-- m_nPos
//                      |==| |
//                Thumb |==| |- <-- m_nPage
//                      |==| |
//                      |==|-`
//                      |  |
//                      |  |
//                      |  |
//                      |  |
//                      |  |
//                      |  | <-- m_nMax - m_nPage
//                      |  |     (max. thumb pos.)
//                      |  |
//                      |--| <-- m_nMax
//  Scroll arrow (down) |__|
//

#define SBMSG_OFFSET_CHANGE 1

class Scrollbar : public BasePanel
{
public:
    virtual LPCTSTR ClassName() { return TEXT("mb_Scrollbar"); }
    static Scrollbar *Create(HWND hWndParent);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate();
    void PaintContent(PAINTSTRUCT *pps);

public:
    int m_nMin;
    int m_nMax;
    int m_nPage;
    int m_nPos;
    int m_nTrackPos;

public:
    int m_PageHeight;
    int m_PageOffset;
    int m_OffsetIncrement;

public:
    // void SetClientHeight(int h);
    void SetPageHeight(int h);
    int GetPageOffset(void);
    void SetPageOffset(int y);
    void IncrementPageOffset(void);
    void DecrementPageOffset(void);
    void GetTopButtonRect(RECT *r);
    void GetBottomButtonRect(RECT *r);
    void GetThumbRect(RECT *r);
    int GetRelativeHorizontalDistance(int d);
};



#endif // __SCROLLBAR_H__
