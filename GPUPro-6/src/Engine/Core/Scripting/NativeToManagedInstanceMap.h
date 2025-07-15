#pragma once

#include <vector>
#include <unordered_map>

#include "Engine/Core/RTTI/RTTI.h"

class ManagedObject;

struct NativeToManagedInstance
{
	InstanceID m_nativeInstanceId;
	InstanceID m_managedObjectId;

	NativeToManagedInstance(InstanceID nativeInstanceId,
		InstanceID managedObjectId) :
		m_nativeInstanceId(nativeInstanceId),
		m_managedObjectId(managedObjectId) { }
};

class NativeToManagedInstanceMap
{
public:
	ManagedObject* GetManagedObject(TypeID nativeTypeId, InstanceID nativeObjectId);
	ITypedObject* GetNativeObject(ManagedTypeID managedTypeId, InstanceID managedObjectId);

	InstanceID GetNativeInstanceID(TypeID nativeTypeId, InstanceID managedInstanceId);
	InstanceID GetManagedInstanceID(TypeID nativeTypeId,  InstanceID nativeInstanceId);
	ManagedTypeID GetManagedTypeID(TypeID nativeTypeId);
	TypeID GetNativeTypeID(ManagedTypeID managedTypeId);

	void CreateTypeMapping(TypeID nativeTypeId, ManagedTypeID managedTypeId);
	void CreateInstanceMapping(TypeID nativeTypeId, NativeToManagedInstance instanceMapping);

private:
	struct TypeMapping
	{
		TypeID m_nativeTypeId;
		ManagedTypeID m_managedTypeId;
	};
	std::vector<TypeMapping> m_typeMapping;
	std::unordered_map<TypeID, std::vector<NativeToManagedInstance>> m_activeMappedInstances;
};