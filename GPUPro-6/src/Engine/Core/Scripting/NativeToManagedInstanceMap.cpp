#include "stdafx.h"
#include "NativeToManagedInstanceMap.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

ManagedObject* NativeToManagedInstanceMap::GetManagedObject(TypeID nativeTypeId, InstanceID nativeObjectId)
{
	std::vector<NativeToManagedInstance>& activeInstances = m_activeMappedInstances.at(nativeTypeId);
	for (unsigned int i = 0; i < activeInstances.size(); i++)
	{
		NativeToManagedInstance obj = activeInstances[i];
		if (obj.m_nativeInstanceId == nativeObjectId)
		{
			TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
			ManagedObject* mo = tom->GetInstance<ManagedObject>(obj.m_managedObjectId);
			return mo;
		}
	}
	return nullptr;
}

ITypedObject* NativeToManagedInstanceMap::GetNativeObject(ManagedTypeID managedTypeId, InstanceID managedObjectId)
{
	TypeID nativeTypeId = GetNativeTypeID(managedTypeId);
	std::vector<NativeToManagedInstance>& activeInstances = m_activeMappedInstances.at(nativeTypeId);
	for (unsigned int i = 0; i < activeInstances.size(); i++)
	{
		NativeToManagedInstance obj = activeInstances[i];
		if (obj.m_managedObjectId == managedObjectId)
		{
			TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
			ITypedObject* to = tom->GetInstance(nativeTypeId, obj.m_nativeInstanceId);
			return to;
		}
	}
	return nullptr;
}

InstanceID NativeToManagedInstanceMap::GetNativeInstanceID(TypeID nativeTypeId, InstanceID managedInstanceId)
{
	std::vector<NativeToManagedInstance>& activeInstances = m_activeMappedInstances.at(nativeTypeId);
	for (unsigned int i = 0; i < activeInstances.size(); i++)
	{
		NativeToManagedInstance obj = activeInstances[i];
		if (obj.m_managedObjectId == managedInstanceId)
		{
			return obj.m_nativeInstanceId;
		}
	}
	return InvalidInstanceID;
}

InstanceID NativeToManagedInstanceMap::GetManagedInstanceID(TypeID nativeTypeId, InstanceID nativeInstanceId)
{
	std::vector<NativeToManagedInstance>& activeInstances = m_activeMappedInstances.at(nativeTypeId);
	for (unsigned int i = 0; i < activeInstances.size(); i++)
	{
		NativeToManagedInstance obj = activeInstances[i];
		if (obj.m_nativeInstanceId == nativeInstanceId)
		{
			return obj.m_managedObjectId;
		}
	}
	return InvalidInstanceID;
}

ManagedTypeID NativeToManagedInstanceMap::GetManagedTypeID(TypeID nativeTypeId)
{
	for (unsigned int i = 0; i < m_typeMapping.size(); i++)
	{
		if (m_typeMapping[i].m_nativeTypeId == nativeTypeId)
		{
			return m_typeMapping[i].m_managedTypeId;
		}
	}
	return nullptr;
}

TypeID NativeToManagedInstanceMap::GetNativeTypeID(ManagedTypeID managedTypeId)
{
	for (unsigned int i = 0; i < m_typeMapping.size(); i++)
	{
		if (m_typeMapping[i].m_managedTypeId == managedTypeId)
		{
			return m_typeMapping[i].m_nativeTypeId;
		}
	}
	return nullptr;
}

void NativeToManagedInstanceMap::CreateTypeMapping(TypeID nativeTypeId, ManagedTypeID managedTypeId)
{
	m_typeMapping.push_back({ nativeTypeId, managedTypeId });
}

void NativeToManagedInstanceMap::CreateInstanceMapping(TypeID nativeTypeId, NativeToManagedInstance instanceMapping)
{
	m_activeMappedInstances[nativeTypeId].push_back(instanceMapping);
}
