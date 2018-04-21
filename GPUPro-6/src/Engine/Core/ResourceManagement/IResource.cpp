#include "stdafx.h"
#include "IResource.h"

ManagedObject* IResource::GetManagedObject()
{
	return m_managedObject;
}

size_t IResource::GetResourceIndex()
{
	return m_resourceIndex;
}

void IResource::Initialize()
{
	const char* managedClassName = GetName();
	m_managedObject = ManagedObject::ConstructManagedObject(managedClassName);
}

void IResource::Release()
{
	ManagedObject::ReleaseManagedObject(&m_managedObject);
}

void IResource::SetResourceIndex(size_t resourceIndex)
{
	m_resourceIndex = resourceIndex;
	m_managedObject->SetFieldValue("m_resourceIndex", &m_resourceIndex);
}

IResource::IResource()
{
}

IResource::~IResource()
{
}
