#pragma once

class ISystem
{
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


private:
	bool m_initialized = false;
};
