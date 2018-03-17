#include "stdafx.h"
#include "SystemContainer.h"

#include "ISystem.h"

void SystemContainer::InitializeAll()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->Initialize();
	}
}

void SystemContainer::FixedTickAll()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->FixedTick();
	}
}

void SystemContainer::EarlyVariableTickAll()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->EarlyVariableTick();
	}
}

void SystemContainer::VariableTickAll()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->VariableTick();
	}
}

void SystemContainer::LateVariableTickAll()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->LateVariableTick();
	}
}

void SystemContainer::DeinitializeAll()
{
	for (std::vector<std::shared_ptr<ISystem>>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		it->get()->Deinitalize();
	}
}
