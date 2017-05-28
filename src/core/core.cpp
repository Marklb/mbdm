#include "core.h"

Core::Core(void)
{
    printf("Creating Core\n");
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);

    currSimDesktopWin = CurrentSimulatedDesktopWindow::Create();
    currSimDesktopWin->EnableBorder(false);
    currSimDesktopWin->SetPosition((screenWidth/2)-(400/2),10);
    currSimDesktopWin->SetSize(400,40);
    ShowWindow(currSimDesktopWin->GetHWND(),SW_SHOW);
}

Core::~Core(void)
{

}
