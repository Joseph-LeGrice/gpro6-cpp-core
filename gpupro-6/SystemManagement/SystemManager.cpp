#include "stdafx.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/TimeSystem.h"

SystemManager* SystemManager::s_instance = new SystemManager();

SystemManager::~SystemManager()
{

}

SystemManager::SystemManager()
{
}

int SystemManager::DoRunGameLoop()
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

void SystemManager::DoDeinitialize()
{
    for (auto it = m_map.begin(); it != m_map.end(); ++it)
    {
        it->second->Deinitalize();
        delete it->second;
    }
}
