#include "stdafx.h"
#include "NativeToManagedInstanceMap.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

ManagedObject* NativeToManagedInstanceMap::GetManagedObject(TypeID nativeTypeId, InstanceID nativeObjectId)
{
	std::vector<NativeToManagedInstance>& activeInstances = m_activeMappedInstances.at(nativeTypeId);
	for (int i = 0; i < activeInstances.size(); i++)
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

InstanceID NativeToManagedInstanceMap::GetNativeInstanceID(TypeID nativeTypeId, InstanceID managedInstanceId)
{
	std::vector<NativeToManagedInstance>& activeInstances = m_activeMappedInstances.at(nativeTypeId);
	for (int i = 0; i < activeInstances.size(); i++)
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
	for (int i = 0; i < activeInstances.size(); i++)
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
	return m_typeMapping[nativeTypeId];
}

void NativeToManagedInstanceMap::CreateTypeMapping(TypeID nativeTypeId, ManagedTypeID managedTypeId)
{
	m_typeMapping.insert({ nativeTypeId, managedTypeId });
}

void NativeToManagedInstanceMap::CreateInstanceMapping(TypeID nativeTypeId, NativeToManagedInstance instanceMapping)
{
	m_activeMappedInstances[nativeTypeId].push_back(instanceMapping);
}
