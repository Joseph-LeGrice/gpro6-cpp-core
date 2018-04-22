#include "stdafx.h"
#include "IResource.h"

ManagedObject* IResource::GetManagedObject()
{
	return m_managedObject;
}

void IResource::Initialize()
{
	const char* managedClassName = GetTypeName();
	m_managedObject = ManagedObject::ConstructManagedObject(managedClassName);
}

void IResource::Release()
{
	ManagedObject::ReleaseManagedObject(&m_managedObject);
}

IResource::IResource()
{
}

IResource::~IResource()
{
}
