#pragma once

class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() noexcept = default;
	ISystem(const ISystem&) = delete;

	bool IsInitialized()
	{
		return m_initialized;
	}

	virtual void Initialize() { m_initialized = true; }
	virtual void FixedTick() { }
	virtual void EarlyVariableTick() { }
    virtual void VariableTick() { }
    virtual void LateVariableTick() { }
    virtual void Deinitalize() { }

private:
	bool m_initialized = false;
};
