#pragma once
#include "GameSystem.h"

class ISystem
{
public:
	ISystem();
	virtual ~ISystem();
	ISystem(const ISystem&) = delete;

	virtual void FixedTick();
	virtual void VariableTick();
};

#define REGISTER_SUBSYSTEM(x) \
public: \
static x* Instance() \
{ \
	static_assert(std::is_base_of<ISystem, x>::value, "Must be Sub-Class of ISystem"); \
	return GameSystem::GetSystem<x>(); \
} \
x(const x&) = delete; \
x(); \
virtual ~x();
