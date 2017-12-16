#pragma once

class ISystem
{
public:
	ISystem();
	virtual ~ISystem();
	ISystem(const ISystem&) = delete;

    virtual bool Initialize();
    virtual void FixedTick();
    virtual void EarlyVariableTick();
    virtual void VariableTick();
    virtual void LateVariableTick();
    virtual void Deinitalize();
};
