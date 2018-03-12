#include "stdafx.h"
#include "GameLoop.h"

#include "Engine/Core/Time/Time.h"
#include "Engine/Core/SystemManagement/ISystem.h"

int GameLoop::Run()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->Initialize();
	}

	m_running = true;
    while (m_running)
    {
		try
		{
			m_time.AdvanceFrame();

			while (m_time.ShouldAdvanceFixedStep())
			{
				for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
					it != m_systems.end(); it++) {
					it->get()->FixedTick();
				}
			}

			for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
				it != m_systems.end(); it++) {
				it->get()->EarlyVariableTick();
			}

			for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
				it != m_systems.end(); it++) {
				it->get()->VariableTick();
			}

			for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
				it != m_systems.end(); it++) {
				it->get()->LateVariableTick();
			}
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

	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->Deinitalize();
	}

    return 0;
}

void GameLoop::Stop()
{
    m_running = false;
}
