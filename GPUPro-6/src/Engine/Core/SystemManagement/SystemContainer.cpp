#include "stdafx.h"
#include "SystemContainer.h"

#include "ISystem.h"

void SystemContainer::InitializeAll()
{
	for (std::vector<ISystem*>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		(*it)->Initialize();
	}
}

void SystemContainer::FixedTickAll()
{
	for (std::vector<ISystem*>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		(*it)->FixedTick();
	}
}

void SystemContainer::EarlyVariableTickAll()
{
	for (std::vector<ISystem*>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		(*it)->EarlyVariableTick();
	}
}

void SystemContainer::VariableTickAll()
{
	for (std::vector<ISystem*>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		(*it)->VariableTick();
	}
}

void SystemContainer::LateVariableTickAll()
{
	for (std::vector<ISystem*>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		(*it)->LateVariableTick();
	}
}

void SystemContainer::DeinitializeAll()
{
	for (std::vector<ISystem*>::iterator it = m_systems.begin();
		it != m_systems.end(); it++) {
		(*it)->Deinitalize();
	}
}
