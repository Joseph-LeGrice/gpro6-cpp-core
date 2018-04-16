#include "stdafx.h"
#include "IResource.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"

MonoObject* IResource::GetManagedObject()
{
	return mono_gchandle_get_target(m_objectHandle);
}

size_t IResource::GetResourceIndex()
{
	return m_resourceIndex;
}

void IResource::SetResourceIndex(size_t resourceIndex)
{
	m_resourceIndex = resourceIndex;

	MonoObject* managedObject = GetManagedObject();
	MonoClass* managedClass = mono_object_get_class(managedObject);
	MonoClassField* field = mono_class_get_field_from_name(managedClass, "m_resourceIndex");
	mono_field_set_value(managedObject, field, &m_resourceIndex);
}

void IResource::ConstructManagedObject()
{
	ScriptedSystemLoader* monoLoader = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	MonoObject* managedObject = monoLoader->CreateObject(GetName());
	m_objectHandle = mono_gchandle_new(managedObject, FALSE);
}

void IResource::ReleaseManagedObject()
{
	mono_gchandle_free(m_objectHandle);
}

IResource::IResource()
{
}

IResource::~IResource()
{
}
