#include "simulated_desktops_manager.h"

SimulatedDesktopsManager::SimulatedDesktopsManager(void)
: m_CurrentMode(SimulatedDesktopsManager::MODE_NORMAL)
{

}

SimulatedDesktopsManager::~SimulatedDesktopsManager(void)
{

}

void SimulatedDesktopsManager::SetMode(int m)
{
    m_CurrentMode = m;
}

int SimulatedDesktopsManager::GetMode(void)
{
    return m_CurrentMode;
}
