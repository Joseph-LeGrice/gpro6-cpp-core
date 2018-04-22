#include "stdafx.h"
#include "ManagedObject.h"
#include "Engine/Core/GlobalStaticReferences.h"

#include "Engine/Core/Scripting/ScriptedSystemLoader.h"

ManagedObject::~ManagedObject()
{
	if (m_objectHandle != 0)
	{
		mono_gchandle_free(m_objectHandle);
	}
}

MonoObject* ManagedObject::GetManagedObject()
{
	return mono_gchandle_get_target(m_objectHandle);
}

void ManagedObject::SetFieldValue(const char* fieldName, void* value)
{
	MonoObject* managedObject = GetManagedObject();
	MonoClass* managedClass = mono_object_get_class(managedObject);
	MonoClassField* field = mono_class_get_field_from_name(managedClass, fieldName);
	mono_field_set_value(managedObject, field, value);
}
