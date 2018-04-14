#pragma once

#include <vector>

class ISystem
{
	friend class SystemContainer;

public:
	ISystem() = default;
	virtual ~ISystem() noexcept = default;
	ISystem(const ISystem&) = delete;

	virtual void Initialize() { m_initialized = true; }
	virtual void FixedTick() { }
	virtual void EarlyVariableTick() { }
	virtual void VariableTick() { }
	virtual void LateVariableTick() { }
	virtual void Deinitalize() { m_initialized = false; }

	bool IsInitialized()
	{
		return m_initialized;
	}

	void RegisterSubsystem(ISystem* system)
	{
		int systemIndex = system->m_systemIndex;
		custom_assert::is_true(systemIndex >= 0, "Trying to register invalid system");
		m_subsystems.push_back(systemIndex);
	}

	void UnregisterSubsystem(ISystem* system)
	{
		int systemIndex = system->m_systemIndex;
		custom_assert::is_true(systemIndex >= 0, "Trying to unregister invalid system");
		for (int i = 0; i < m_subsystems.size(); i++)
		{
			int subsystemIndex = m_subsystems[i];
			if (subsystemIndex == systemIndex)
			{
				int newSize = static_cast<int>(m_subsystems.size() - 1);
				m_subsystems[i] = m_subsystems[newSize];
				m_subsystems.resize(newSize);

				break;
			}
		}
	}

private:
	bool m_initialized = false;
	int m_systemIndex = -1;
	
	std::vector<int> m_subsystems;
};
