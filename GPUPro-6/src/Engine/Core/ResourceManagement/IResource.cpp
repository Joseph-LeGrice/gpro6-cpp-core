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

void IResource::ConstructManagedObject()
{
	ScriptedSystemLoader* monoLoader = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	MonoObject* managedObject = monoLoader->CreateObject(GetName());
	m_objectHandle = mono_gchandle_new(managedObject, FALSE);
}

IResource::IResource()
{
}

IResource::~IResource()
{
	mono_gchandle_free(m_objectHandle);
}
