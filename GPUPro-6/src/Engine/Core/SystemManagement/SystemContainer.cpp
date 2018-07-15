#include "stdafx.h"
#include "SystemContainer.h"

#include "ISystem.h"


void SystemContainer::RegisterSystem(ISystem* newSystem)
{
	newSystem->m_systemIndex = static_cast<int>(m_systems.size());
	m_systems.push_back(newSystem);
}

void SystemContainer::InitializeAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		if (!(*it)->IsInitialized()) {
			(*it)->Initialize();
		}
	}
}

void SystemContainer::FixedTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		if ((*it)->IsInitialized()) {
			(*it)->FixedTick();
		}
	}
}

void SystemContainer::EarlyVariableTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		if ((*it)->IsInitialized()) {
			(*it)->EarlyVariableTick();
		}
	}
}

void SystemContainer::VariableTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		if ((*it)->IsInitialized()) {
			(*it)->VariableTick();
		}
	}
}

void SystemContainer::LateVariableTickAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++) {
		if ((*it)->IsInitialized()) {
			(*it)->LateVariableTick();
		}
	}
}

void SystemContainer::DeinitializeAll()
{
	auto systems = m_systems;
	for (std::vector<ISystem*>::iterator it = systems.begin();
		it != systems.end(); it++)
	{
		ISystem* system = *it;
		std::vector<int> subsystemIndexes = system->m_subsystems;
		for (unsigned int i = 0; i < subsystemIndexes.size(); i++)
		{
			int ssIndex = subsystemIndexes[i];
			ISystem* sSystem = systems[ssIndex];
			if (sSystem->IsInitialized()) {
				sSystem->Deinitalize();
			}
		}

		if (system->IsInitialized()) {
			system->Deinitalize();
		}
	}
}
