#include "stdafx.h"
#include "NativeToManagedInstanceMap.h"
#include "ManagedObject.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

ManagedObject* NativeToManagedInstanceMap::GetManagedObject(TypeID nativeTypeId, InstanceID nativeObjectId)
{
	for (int i = 0; i < m_nativeManagedObjects.size(); i++)
	{
		NativeToManagedObject ntmo = m_nativeManagedObjects[i];
		if (ntmo.m_nativeTypeId == nativeTypeId && 
			ntmo.m_nativeInstanceId == nativeObjectId)
		{
			TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
			ManagedObject* mo = tom->GetInstance<ManagedObject>(ntmo.m_managedObjectId);
			return mo;
		}
	}
	return nullptr;
}

void NativeToManagedInstanceMap::CreateMapping(NativeToManagedObject ntmo)
{
	m_nativeManagedObjects.push_back(ntmo);
}
