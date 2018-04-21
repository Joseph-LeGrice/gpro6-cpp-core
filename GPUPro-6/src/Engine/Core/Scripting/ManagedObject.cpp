#include "stdafx.h"
#include "ManagedObject.h"
#include "Engine/Core/GlobalStaticReferences.h"

#include "Engine/Core/Scripting/ScriptedSystemLoader.h"

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

ManagedObject* ManagedObject::ConstructManagedObject(const char* className)
{
	ScriptedSystemLoader* monoLoader = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	MonoObject* managedObject = monoLoader->CreateObject(className);
	ManagedObjectID objId = mono_gchandle_new(managedObject, FALSE);
	return new ManagedObject(objId);
}

void ManagedObject::ReleaseManagedObject(ManagedObject** obj)
{
	ManagedObject* objPointer = *obj;
	mono_gchandle_free(objPointer->m_objectHandle);
	delete objPointer;
	obj = nullptr;
}