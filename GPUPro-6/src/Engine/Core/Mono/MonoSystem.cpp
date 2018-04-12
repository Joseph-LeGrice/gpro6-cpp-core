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
	else
	{
		funcPointer = nullptr;
	}
}

void MonoSystem::CallMethod(MonoSimpleMethodStub& funcPointer)
{
	if (funcPointer != nullptr)
	{
		MonoException* ex = NULL;
		funcPointer(m_object, &ex);

		if (ex != nullptr)
		{
		}
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
	CallMethod(m_initMethod);
}

void MonoSystem::Deinitalize()
{
	CallMethod(m_deinitMethod);
}

void MonoSystem::FixedTick()
{
	CallMethod(m_fixedTickMethod);
}

void MonoSystem::EarlyVariableTick()
{
	CallMethod(m_earlyVariableTickMethod);
}

void MonoSystem::VariableTick()
{
	CallMethod(m_variableTickMethod);
}

void MonoSystem::LateVariableTick()
{
	CallMethod(m_lateVariableTickMethod);
}
