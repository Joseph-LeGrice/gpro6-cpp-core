#include "stdafx.h"
#include "SystemManagement/SystemManagement.h"

SystemManagement* SystemManagement::s_instance = new SystemManagement();

void SystemManagement::Initialize()
{
    s_instance->DoInitialize();
}

int SystemManagement::RunGameLoop()
{
    return s_instance->DoRunGameLoop();
}

void SystemManagement::Deinitialize()
{
    s_instance->DoDeinitialize();
    delete s_instance;
}

SystemManagement::~SystemManagement()
{

}

SystemManagement::SystemManagement()
{

}

void SystemManagement::DoInitialize()
{
    m_config.m_systemInstance;
    //GetNextConfiguration(m_config);
    //while (ISystem* thisSystem = )
}

int SystemManagement::DoRunGameLoop()
{
    /*
    try
    {
    TimeSystem* time = GetSystem<TimeSystem>();

    m_running = true;
    while (m_running)
    {
    while (time->ShouldAdvanceFixedStep())
    {
    for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
    {
    it->second->FixedTick();
    }
    }

    for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
    {
    auto sys = it->second;
    sys->VariableTick();
    }

    time->AdvanceFrame();
    }
    }
    catch (...)
    {

    }
    */
    return 0;
}

void SystemManagement::DoDeinitialize()
{
}
