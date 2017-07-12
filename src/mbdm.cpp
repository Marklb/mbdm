#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <tchar.h>

#include "common.h"
#include "core/core.h"
#include "windows/settings_window.h"
#include "windows/debug_window.h"


HINSTANCE g_hInst;


FILE *g_ic_file_cout_stream; FILE *g_ic_file_cin_stream;
// Success: true , Failure: false
bool InitConsole()
{
    if (!AllocConsole()) { return false; }
    if (freopen_s(&g_ic_file_cout_stream, "CONOUT$", "w", stdout) != 0) { return false; } // For std::cout
    if (freopen_s(&g_ic_file_cin_stream, "CONIN$", "w+", stdin) != 0) { return false; } // For std::cin
    return true;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
    g_hInst = hInstance;
    InitConsole();
    HWND hWndConsole = GetConsoleWindow();
    SetWindowPos(hWndConsole,NULL,1000,10,NULL,NULL,SWP_NOACTIVATE | SWP_NOSIZE
        | SWP_NOOWNERZORDER | SWP_NOZORDER);
    // printf("----[mbdm]----\n");


    // https://github.com/melak47/BorderlessWindow/blob/master/BorderlessWindow/src/BorderlessWindow.cpp


    SettingsWindow *prw = SettingsWindow::Create();
    // // prw->SetPosition(-1000, 200);
    // prw->SetPosition(10+1980, 10-170);
    // // prw->SetSize(1000, 700);
    // // prw->SetSize(625, 700);
    // prw->SetSize(1700, 1000);

    prw->SetPosition(5, 5);
    prw->SetSize(1000, 600);
    ShowWindow(prw->GetHWND(), nCmdShow);

    // SettingsWindow *prw2 = SettingsWindow::Create();
    // ShowWindow(prw2->GetHWND(), SW_SHOW);
    // SetWindowLongPtr(prw2->GetHWND(), GWL_STYLE, WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
    // prw2->RemBorder();
    // SetWindowPos(prw2->GetHWND(), NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);



    Core core;


    DebugWindow *debugWin = DebugWindow::Create();
    // debugWin->SetPosition(-1600, 10+150);
    // debugWin->SetSize(1600, 850);
    debugWin->SetPosition(5, 5);
    debugWin->SetSize(1000, 600);
    ShowWindow(debugWin->GetHWND(), SW_SHOW);


    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}
