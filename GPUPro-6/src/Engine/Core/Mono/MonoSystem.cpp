#include "stdafx.h"
#include "MonoSystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#pragma warning(pop)

MonoSystem::MonoSystem(MonoObject* object)
{
	m_object = object;
	m_class = mono_object_get_class(object);
	//mono_class_get_method_from_name()
}

void MonoSystem::Initialize()
{
}

void MonoSystem::Deinitalize()
{
}

void MonoSystem::FixedTick()
{
}

void MonoSystem::EarlyVariableTick()
{
}

void MonoSystem::VariableTick()
{
}

void MonoSystem::LateVariableTick()
{
}
