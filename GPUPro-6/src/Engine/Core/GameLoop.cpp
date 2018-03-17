#include "stdafx.h"
#include "GameLoop.h"

#include "Engine/Core/Time/Time.h"
#include "Engine/Core/SystemManagement/SystemContainer.h"

int GameLoop::Run(SystemContainer& systems)
{
	systems.InitializeAll();

	m_running = true;
    while (m_running)
    {
		try
		{
			m_time.AdvanceFrame();

			while (m_time.ShouldAdvanceFixedStep())
			{
				systems.FixedTickAll();
			}

			systems.EarlyVariableTickAll();
			systems.VariableTickAll();
			systems.LateVariableTickAll();
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

	systems.DeinitializeAll();

    return 0;
}

void GameLoop::Stop()
{
    m_running = false;
}
