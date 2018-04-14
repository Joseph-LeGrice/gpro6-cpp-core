#include "stdafx.h"
#include "ScriptedSystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#pragma warning(pop)

void ScriptedSystem::GetMethodThunk(const char* methodName, MonoSimpleMethodStub& funcPointer)
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

void ScriptedSystem::CallMethod(MonoSimpleMethodStub& funcPointer)
{
	if (funcPointer != nullptr)
	{
		MonoObject* obj = mono_gchandle_get_target(m_objectHandle);
		MonoException* ex = NULL;

		funcPointer(obj, &ex);

		if (ex != nullptr)
		{
			Log("Exception Thrown");
		}
	}
}

ScriptedSystem::ScriptedSystem(MonoObject* object)
{
	m_objectHandle = mono_gchandle_new(object, FALSE);
	m_class = mono_object_get_class(object);

	GetMethodThunk("Initialize", m_initMethod);
	GetMethodThunk("Deinitialize", m_deinitMethod);
	GetMethodThunk("FixedTick", m_fixedTickMethod);
	GetMethodThunk("EarlyVariableTick", m_earlyVariableTickMethod);
	GetMethodThunk("VariableTick", m_variableTickMethod);
	GetMethodThunk("LateVariableTick", m_lateVariableTickMethod);
}

void ScriptedSystem::Initialize()
{
	ISystem::Initialize();
	CallMethod(m_initMethod);
}

void ScriptedSystem::Deinitalize()
{
	ISystem::Deinitalize();
	CallMethod(m_deinitMethod);
	mono_gchandle_free(m_objectHandle);
}

void ScriptedSystem::FixedTick()
{
	CallMethod(m_fixedTickMethod);
}

void ScriptedSystem::EarlyVariableTick()
{
	CallMethod(m_earlyVariableTickMethod);
}

void ScriptedSystem::VariableTick()
{
	CallMethod(m_variableTickMethod);
}

void ScriptedSystem::LateVariableTick()
{
	CallMethod(m_lateVariableTickMethod);
}
