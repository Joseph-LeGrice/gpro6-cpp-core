#include "stdafx.h"
#include "SystemManagement/SystemManagement.h"

SystemManagement* SystemManagement::s_instance = new SystemManagement();

SystemManagement::~SystemManagement()
{

}

SystemManagement::SystemManagement()
{
}

int SystemManagement::DoRunGameLoop()
{
    try
    {
        TimeSystem& timeSystem = *GetSystem<TimeSystem>();

        m_running = true;
        while (m_running)
        {
            while (timeSystem.ShouldAdvanceFixedStep())
            {
                for (auto it = m_map.begin(); it != m_map.end(); ++it)
                {
                    it->second->FixedTick();
                }
            }

            for (auto it = m_map.begin(); it != m_map.end(); ++it)
            {
                it->second->VariableTick();
            }

            timeSystem.AdvanceFrame();
        }
    }
    catch (...)
    {

    }

    return 0;
}

void SystemManagement::DoDeinitialize()
{
    for (auto it = m_map.begin(); it != m_map.end(); ++it)
    {
        it->second->Deinitalize();
        delete it->second;
    }
}
