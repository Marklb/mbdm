#ifndef __CORE_H__
#define __CORE_H__

#include <windows.h>

#include "../common.h"
#include "../windows/current_simulated_desktop_window.h"
#include "global_kb_handler.h"

class Core
{
public:
    Core(void);
    ~Core(void);

public:
    CurrentSimulatedDesktopWindow *currSimDesktopWin;

};


#endif // __CORE_H__
