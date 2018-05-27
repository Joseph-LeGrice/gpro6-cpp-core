#include "stdafx.h"
#include "RTTI.h"

#include "ITypedObject.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "TypedObjectManager.h"

ToPtr::ToPtr(TypeID typeId, InstanceID instanceId) : m_typeId(typeId),
m_instanceId(instanceId) { }

ToPtr::ToPtr(ITypedObject* obj) : m_typeId(obj->GetTypeID()),
m_instanceId(obj->GetInstanceID()) { }

ToPtr::ToPtr() : m_typeId(""), m_instanceId(-1) { }

TypeID ToPtr::GetTypeID()
{
	return m_typeId;
}

InstanceID ToPtr::GetInstanceID()
{
	return m_instanceId;
}

ToPtr::operator bool()
{
	return m_instanceId > -1 && m_typeId != "";
}

ToPtr::operator ITypedObject*()
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	return tom->GetInstance(m_typeId, m_instanceId);
}

void ToPtr::operator=(ITypedObject* obj)
{
	m_typeId = obj->GetTypeID();
	m_instanceId = obj->GetInstanceID();
}
