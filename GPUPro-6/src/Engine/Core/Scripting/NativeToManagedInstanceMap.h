#pragma once

#include <vector>
#include "Engine/Core/RTTI/RTTI.h"
class ManagedObject;

struct NativeToManagedObject
{
	TypeID m_nativeTypeId;
	InstanceID m_nativeInstanceId;
	InstanceID m_managedObjectId;
};

class NativeToManagedInstanceMap
{
public:
	ManagedObject* GetManagedObject(TypeID nativeTypeId, InstanceID nativeObjectId);
	void CreateMapping(NativeToManagedObject ntmo);

private:
	std::vector<NativeToManagedObject> m_nativeManagedObjects;
};