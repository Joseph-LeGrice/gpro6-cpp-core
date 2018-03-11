#pragma once

class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() noexcept = default;
	ISystem(const ISystem&) = delete;

	virtual bool Initialize() { return true; }
	virtual void FixedTick() { }
	virtual void EarlyVariableTick() { }
    virtual void VariableTick() { }
    virtual void LateVariableTick() { }
    virtual void Deinitalize() { }
};
