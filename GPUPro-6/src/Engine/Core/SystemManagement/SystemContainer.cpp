#include "stdafx.h"
#include "SystemContainer.h"

#include "ISystem.h"


void SystemContainer::RegisterSystem(ISystem* newSystem)
{
	m_systems.push_back(newSystem);
}

void SystemContainer::InitializeAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		(*it)->Initialize();
	}
}

void SystemContainer::FixedTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		(*it)->FixedTick();
	}
}

void SystemContainer::EarlyVariableTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		(*it)->EarlyVariableTick();
	}
}

void SystemContainer::VariableTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		(*it)->VariableTick();
	}
}

void SystemContainer::LateVariableTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		(*it)->LateVariableTick();
	}
}

void SystemContainer::DeinitializeAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		(*it)->Deinitalize();
	}
}
