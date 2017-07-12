#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <tchar.h>

#include "common.h"
#include "core/core.h"
#include "windows/settings_window.h"
#include "custom.h"

HINSTANCE g_hInst;

MSG Message;


// char MbDesktopName1[256] = "MB Desktop 1";
// int MbDesktopName1Len = 12;

// HWND IDC_EDIT_RECOLOR;

// RECT tClientRect;
// HRGN tBgRgn;
// HBRUSH tHBrush;



static HWND hwndCustom;

#define CUSTOM_ID     100
#define MARGIN          7

static LRESULT CALLBACK
MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_SIZE:
            if(wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED) {
                WORD cx = LOWORD(lParam);
                WORD cy = HIWORD(lParam);
                SetWindowPos(hwndCustom, NULL, MARGIN, MARGIN,
                             cx-2*MARGIN, cy-2*MARGIN, SWP_NOZORDER);
            }
            break;

        case WM_CREATE:
            hwndCustom = CreateWindow(CUSTOM_WC, NULL, WS_CHILD | WS_VISIBLE,
                                  0, 0, 0, 0, hwnd, (HMENU) CUSTOM_ID, g_hInst, NULL);
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  RECT clientRect;
  RECT rectInner;
  HRGN bgRgn;
  HBRUSH hBrush;
  // HPEN hPen;


	switch (Message)
	{
	case WM_PAINT:
    printf("WM_PAINT\n");
		// Render();
    hdc = BeginPaint(hWnd, &ps);
    // if(hWnd == wrkspListWin.hWnd){
    //   WorkspaceListWindow_Render(&wrkspListWin, &hdc);
    // }

        // GetClientRect(hWnd, &clientRect);
        // bgRgn = CreateRectRgnIndirect(&clientRect);
        // hBrush = CreateSolidBrush(RGB(60,0,80));
        // FillRgn(hdc, bgRgn, hBrush);
        //
        // rectInner.left = clientRect.left + borderSize;
        // rectInner.top = clientRect.top + borderSize;
        // rectInner.right = clientRect.right - borderSize;
        // rectInner.bottom = clientRect.bottom - borderSize;
        // bgRgn = CreateRectRgnIndirect(&rectInner);
        // hBrush = CreateSolidBrush(RGB(0,0,0));
        // FillRgn(hdc, bgRgn, hBrush);
        //
        //
        // rectInner.left = clientRect.left + borderSize;
        // rectInner.top = clientRect.top + borderSize + 0;
        // rectInner.right = clientRect.right - borderSize;
        // rectInner.bottom = clientRect.top + 30;
        // bgRgn = CreateRectRgnIndirect(&rectInner);
        // hBrush = CreateSolidBrush(RGB(0,0,100));
        // FillRgn(hdc, bgRgn, hBrush);
        // SetBkColor(hdc, RGB(0,0,100));
        // SetTextColor(hdc, RGB(255,255,255));
        // DrawText(hdc, MbDesktopName1, MbDesktopName1Len, &rectInner, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        //
        // rectInner.left = clientRect.left + borderSize;
        // rectInner.top = clientRect.top + borderSize + 30;
        // rectInner.right = clientRect.right - borderSize;
        // rectInner.bottom = clientRect.top + 60;
        // bgRgn = CreateRectRgnIndirect(&rectInner);
        // hBrush = CreateSolidBrush(RGB(0,0,100));
        // FillRgn(hdc, bgRgn, hBrush);
        // SetBkColor(hdc, RGB(0,0,100));
        // SetTextColor(hdc, RGB(255,255,255));
        // DrawText(hdc, MbDesktopName1, MbDesktopName1Len, &rectInner, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

        EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:
        printf("WM_CREATE\n");
        // CreateWindow(TEXT("button"), TEXT(""),
		    //          WS_VISIBLE | WS_CHILD | BS_FLAT | BS_OWNERDRAW,
		    //          10, 100, 200, 50,
		    //          hWnd, (HMENU) 1, NULL, NULL);
        // // IDC_EDIT_RECOLOR = CreateWindow(TEXT("edit"), TEXT("Beep"),
		    // //          WS_VISIBLE | WS_CHILD | ES_LEFT | ES_CENTER,
		    // //          20, 50, 80, 25,
		    // //          hWnd, (HMENU) 1, NULL, NULL);
        break;

  case WM_CTLCOLOREDIT:
  {
    printf("WM_CREATE\n");
    // MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
    // hdc = (HDC)wParam;
    // HWND hwndEdit = (HWND)lParam;

    // // MessageBox(NULL, tmp, "Error", MB_ICONERROR);
    // if(hwndEdit == IDC_EDIT_RECOLOR){
    //   SetBkColor(hdc, RGB(0,0,100));
    //   SetDCBrushColor(hdc, RGB(0,0,100));
    //   SetTextColor(hdc, RGB(255,255,255));
    //   return (LRESULT) GetStockObject(DC_BRUSH);
    // }
  }
  break;

  case WM_DRAWITEM:
  {
    printf("WM_DRAWITEM\n");
    // LPDRAWITEMSTRUCT item = (LPDRAWITEMSTRUCT)lParam;
    // if(item->CtlID == 1){
    //   // MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
    //   SetBkColor(item->hDC, RGB(0,0,100));
    //   SetDCBrushColor(item->hDC, RGB(0,0,100));
    //   SetTextColor(item->hDC, RGB(255,255,255));
    //   bgRgn = CreateRectRgnIndirect(&item->rcItem);
    //   hBrush = CreateSolidBrush(RGB(0,0,100));
    //   FillRgn(item->hDC, bgRgn, hBrush);
    //   // DrawText(item->hDC, MbDesktopName1, MbDesktopName1Len, &item->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    //   char tmp[256];
    //   // sprintf(tmp, "Mode: %s", (char *)list.head->data);
    //   // DrawText(item->hDC, tmp, strlen(tmp), &item->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    //   // DrawText(item->hDC, MbDesktopName1, strlen(MbDesktopName1), &item->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    //   mb_Mode *mode;
    //   mode = mb_GetMode(MB_MODE_BASIC);
    //   mode = mb_GetCurrentMode();
    //   sprintf(tmp, "Mode: %s", mode->name);
    //   DrawText(item->hDC, tmp, strlen(tmp), &item->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    // }
  }
  break;

  case WM_COMMAND:
  {
    printf("WM_COMMAND\n");
      //  switch (wParam)
      //  {
      //         case 1:
      //         {
      //           //  SendMessage(lbLogs, LB_ADDSTRING, 0, (LPARAM)TEXT("TEST"));-
      //           MoveWindow(hWnd, 100, 100, 500, 800, TRUE);
      //           break;
      //         }
      //  }
      //  break;
  }

    // case WM_KEYDOWN:
    //     printf("KeyDown: %d\n", counter);
    //     break;

    // case WM_KEYUP:
    //     printf("KeyUp\n");
    //     break;

  //   case WM_CLOSE:
  //       printf("WM_CLOSE\n");
  //       mb_WindowOrganizationModeShowAllProcesses();
  //       DestroyWindow(hWnd);
  //       break;

	// case WM_DESTROY:
  //       printf("WM_DESTROY\n");
  //       mb_WindowOrganizationModeShowAllProcesses();
	//       PostQuitMessage(0);
  //       break;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}


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

    // mb_SetKeyboardHook();

    // int number = 10;
    // char str[256];
    // sprintf_s(str, "It works! - number: %d \n", number);

    // OutputDebugString(str);


    // std::cout << "First sentence." << std::endl;
    //
    // WNDCLASS wc = { 0 };
    // HWND hwnd;
    // MSG msg;
    //
    // // hInstance = hInst;
    //
    // CustomRegister();
    //
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    // wc.lpfnWndProc = MainProc;
    // wc.hInstance = hInstance;
    // wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    // wc.lpszClassName = _T("MainWindow");
    // RegisterClass(&wc);
    //
    // hwnd = CreateWindow(_T("MainWindow"), _T("App Name"), WS_OVERLAPPEDWINDOW,
    //             CW_USEDEFAULT, CW_USEDEFAULT, 550, 250, NULL, NULL, hInstance, NULL);
    // ShowWindow(hwnd, nCmdShow);


    // https://github.com/melak47/BorderlessWindow/blob/master/BorderlessWindow/src/BorderlessWindow.cpp


    SettingsWindow *prw = SettingsWindow::Create();
    // prw->SetPosition(-1000, 200);
    prw->SetPosition(10, 10+200);
    // prw->SetSize(1000, 700);
    // prw->SetSize(625, 700);
    prw->SetSize(1500, 700);
    ShowWindow(prw->GetHWND(), nCmdShow);

    // SettingsWindow *prw2 = SettingsWindow::Create();
    // ShowWindow(prw2->GetHWND(), SW_SHOW);
    // SetWindowLongPtr(prw2->GetHWND(), GWL_STYLE, WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
    // prw2->RemBorder();
    // SetWindowPos(prw2->GetHWND(), NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

    // std::cout << "Creating window2" << std::endl;

    // SetMouseHook();


    Core core;



    while(GetMessage(&Message, NULL, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    // ReleaseMouseHook();
    // mb_ReleaseKeyboardHook();


    CustomUnregister();

	return 0;
}
