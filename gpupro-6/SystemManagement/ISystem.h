#pragma once

class ISystem
{
public:
	ISystem();
	virtual ~ISystem();
	ISystem(const ISystem&) = delete;

    virtual bool InitSystem();
    virtual void FixedTick();
	virtual void VariableTick();
};
