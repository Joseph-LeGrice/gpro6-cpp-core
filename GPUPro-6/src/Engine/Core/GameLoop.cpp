#include "stdafx.h"
#include "GameLoop.h"
#include "Engine/Core/Time/Time.h"
#include "Engine/Core/SystemManagement/SystemManager.h"

StaticPointer<GameLoop> GameLoop::s_instance;

int GameLoop::Run()
{
    return s_instance->InternalRun();
}

void GameLoop::Stop()
{
    s_instance->InternalStop();
}

void DoFixed(ISystem* system)
{
    system->FixedTick();
}

void DoEarlyVariable(ISystem* system)
{
    system->EarlyVariableTick();
}

void DoVariable(ISystem* system)
{
    system->VariableTick();
}

void DoLateVariable(ISystem* system)
{
    system->LateVariableTick();
}

int GameLoop::InternalRun()
{
    m_running = true;
    while (m_running)
    {
		try
		{
            Time::s_instance->AdvanceFrame();

            while (Time::s_instance->ShouldAdvanceFixedStep())
            {
                GetSystemManager().ForEachSystem(DoFixed);
            }

            GetSystemManager().ForEachSystem(DoEarlyVariable);
            GetSystemManager().ForEachSystem(DoVariable);
            GetSystemManager().ForEachSystem(DoLateVariable);
        }
		catch (const custom_assert::custom_assert_error& e)
		{
			Log(e.m_message);
		}
		catch (...)
		{
			break;
		}
    }
    return 0;
}

void GameLoop::InternalStop()
{
    m_running = false;
}
