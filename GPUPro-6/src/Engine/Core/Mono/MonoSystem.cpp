#include "stdafx.h"
#include "MonoSystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#pragma warning(pop)

void MonoSystem::GetMethodThunk(const char* methodName, MonoSimpleMethodStub& funcPointer)
{
	MonoMethod* method = mono_class_get_method_from_name(m_class, methodName, 0);
	if (method != nullptr)
	{
		funcPointer = (MonoSimpleMethodStub)mono_method_get_unmanaged_thunk(method);
	}
}


MonoSystem::MonoSystem(MonoObject* object)
{
	m_object = object;
	m_class = mono_object_get_class(object);

	GetMethodThunk("Initialize", m_initMethod);
	GetMethodThunk("Deinitialize", m_deinitMethod);
	GetMethodThunk("FixedTick", m_fixedTickMethod);
	GetMethodThunk("EarlyVariableTick", m_earlyVariableTickMethod);
	GetMethodThunk("VariableTick", m_variableTickMethod);
	GetMethodThunk("LateVariableTick", m_lateVariableTickMethod);
}

void MonoSystem::Initialize()
{
	if (m_initMethod != nullptr)
	{
		m_initMethod();
	}
}

void MonoSystem::Deinitalize()
{
	if (m_deinitMethod != nullptr)
	{
		m_deinitMethod();
	}
}

void MonoSystem::FixedTick()
{
	if (m_fixedTickMethod != nullptr)
	{
		m_fixedTickMethod();
	}
}

void MonoSystem::EarlyVariableTick()
{
	if (m_earlyVariableTickMethod != nullptr)
	{
		m_earlyVariableTickMethod();
	}
}

void MonoSystem::VariableTick()
{
	if (m_variableTickMethod != nullptr)
	{
		m_variableTickMethod();
	}
}

void MonoSystem::LateVariableTick()
{
	if (m_lateVariableTickMethod != nullptr)
	{
		m_lateVariableTickMethod();
	}
}
