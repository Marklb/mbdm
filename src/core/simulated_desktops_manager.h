#ifndef __SIMULATED_DESKTOPS_MANAGER_H__
#define __SIMULATED_DESKTOPS_MANAGER_H__

#include <windows.h>

#include "../common.h"


class SimulatedDesktopsManager
{
public:
    const static int MODE_NORMAL = 0;
    const static int MODE_ACTIVE = 1;
    const static int MODE_COMMAND = 2;

public:
    SimulatedDesktopsManager(void);
    ~SimulatedDesktopsManager(void);

public:
    int m_CurrentMode;

public:
    void SetMode(int m);
    int GetMode(void);

};


#endif // __SIMULATED_DESKTOPS_MANAGER_H__
