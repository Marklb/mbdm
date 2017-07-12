#ifndef __COMMON_H__
#define __COMMON_H__

#include <windows.h>
#include <iostream>

#include "config.h"

extern HINSTANCE g_hInst;


// NMHDR nmh;
// // nmh.code = CUSTOM_SELCHANGE;    // Message type defined by control.
// nmh.code = WM_LBUTTONDOWN;    // Message type defined by control.
// nmh.idFrom = GetDlgCtrlID(GetHWND());
// nmh.hwndFrom = GetHWND();
// SendMessage(GetParent(GetHWND()),
//     WM_NOTIFY,
//     nmh.idFrom,
//     (LPARAM)&nmh);

struct kb_nmhdr_t{
    NMHDR nmh;
    int vkCode;
}typedef KBNMHDR;

// typedef int *(*msgFn)(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif // __COMMON_H__
