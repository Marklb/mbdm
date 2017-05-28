#include "global_kb_handler.h"



// GlobalKbHandler::GlobalKbHandler(void)
// : m_Hooked(FALSE)
// , m_HookKb(NULL)
// {
//
// }
//
// GlobalKbHandler::~GlobalKbHandler(void)
// {
//     UnHook();
// }
//
// void GlobalKbHandler::Hook(void)
// {
//     if(!(m_HookKb = SetWindowsHookEx(WH_KEYBOARD_LL, &KbHookCallback, NULL, 0)))
//     {
//         MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
//         return;
//     }
//     m_Hooked = TRUE;
// }
//
// void GlobalKbHandler::UnHook(void)
// {
//     UnhookWindowsHookEx(m_HookKb);
// }
//
// LRESULT CALLBACK GlobalKbHandler::KbHookCallback(int nCode, WPARAM wParam, LPARAM lParam){
//     // typedef struct tagKBDLLHOOKSTRUCT {
//     //   DWORD     vkCode;
//     //   DWORD     scanCode;
//     //   DWORD     flags;
//     //   DWORD     time;
//     //   ULONG_PTR dwExtraInfo;
//     // } KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT, *LPKBDLLHOOKSTRUCT;
//     char tmp[256];
//     int ret = 0;
//     if (nCode >= 0)
//     {
//         PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
//         switch(wParam)
//         {
//             case WM_KEYDOWN:
//             {
//                 printf("WM_KEYDOWN: vkCode: %d  0x%x  scanCode: %d\n", p->vkCode, p->vkCode, p->scanCode);
//
//                 switch(p->vkCode)
//                 {
//                     // 0x08: BACKSPACE key
//                     case VK_BACK:
//                     {
//
//                     }
//                     break;
//                 }
//             }
//             break;
//
//             case WM_KEYUP:
//             {
//                 printf("WM_KEYUP: vkCode: %d  0x%x  scanCode: %d\n", p->vkCode, p->vkCode, p->scanCode);
//
//                 switch(p->vkCode)
//                 {
//                     // 0x08: BACKSPACE key
//                     case VK_BACK:
//                     {
//
//                     }
//                     break;
//                 }
//             }
//             break;
//         }
//     }
//
//     // call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
//     return CallNextHookEx(m_HookKb, nCode, wParam, lParam);
// }
