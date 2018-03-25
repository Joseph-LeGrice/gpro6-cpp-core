#pragma once

#include <vector>

class ISystem;

class SystemContainer
{
public:
	SystemContainer(std::vector<ISystem*> systems) :
		m_systems(systems) { }
	SystemContainer(const SystemContainer&) = delete;
	~SystemContainer() = default;

	void InitializeAll();
	void FixedTickAll();
	void EarlyVariableTickAll();
	void VariableTickAll();
	void LateVariableTickAll();
	void DeinitializeAll();

private:
	std::vector<ISystem*> m_systems;
};
