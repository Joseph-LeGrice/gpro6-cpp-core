#include "stdafx.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/TimeSystem.h"
#include <iostream>

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
            timeSystem.AdvanceFrame();
         
            while (timeSystem.ShouldAdvanceFixedStep())
            {
                for (auto it = m_map.begin(); it != m_map.end(); ++it)
                {
                    it->second->FixedTick();
                }
            }

            for (auto it = m_map.begin(); it != m_map.end(); ++it)
            {
                it->second->EarlyVariableTick();
            }

            for (auto it = m_map.begin(); it != m_map.end(); ++it)
            {
                it->second->VariableTick();
            }

            for (auto it = m_map.begin(); it != m_map.end(); ++it)
            {
                it->second->LateVariableTick();
            }
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
