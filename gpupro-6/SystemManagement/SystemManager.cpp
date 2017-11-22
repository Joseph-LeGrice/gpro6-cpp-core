#include "stdafx.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/TimeSystem.h"
//#include "FreeImage.h"
#include <iostream>

SystemManager* SystemManager::s_instance = new SystemManager();
/*
void PrintFreeImageError(FREE_IMAGE_FORMAT fif, const char* message)
{
    std::cout << "***" << std::endl;
    if (fif != FIF_UNKNOWN)
    {
        std::cout << FreeImage_GetFormatFromFIF(fif) << " Format" << std::endl;
    }
    std::cout << message << std::endl;
    std::cout << "***" << std::endl;

}
*/
SystemManager::~SystemManager()
{

}

SystemManager::SystemManager()
{
    //FreeImage_SetOutputMessage(PrintFreeImageError);
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
