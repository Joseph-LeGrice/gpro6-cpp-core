#pragma once

#include <vector>
#include <memory>

class ISystem;

class SystemContainer
{
public:
	SystemContainer(std::vector<std::shared_ptr<ISystem>> systems) :
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
	std::vector<std::shared_ptr<ISystem>> m_systems;
};
