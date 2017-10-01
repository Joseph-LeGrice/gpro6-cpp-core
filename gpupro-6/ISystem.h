#pragma once

class ISystem
{
public:
	ISystem();
	virtual ~ISystem();
	ISystem(const ISystem&) = delete;

	virtual void FixedTick();
	virtual void VariableTick();
};
