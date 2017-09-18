#pragma once
#include "GameSystem.h"

class ISystem
{
public:
	virtual ~ISystem();
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
