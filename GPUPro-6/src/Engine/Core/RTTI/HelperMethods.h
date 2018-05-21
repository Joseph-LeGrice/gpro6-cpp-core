#pragma once

#include "TypeNameMapping.h"
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"

extern void RegisterAllTypes();

template<class T>
ITypedObject* CreateInstance(InstanceID nativeInstanceId)
{
	UNREFERENCED_PARAMETER(nativeInstanceId);
	return new T();
}

template<class T>
ITypedObject* CreateManagedInstance(InstanceID nativeInstanceId)
{
	T* obj = new T();
	TypeID nativeTypeId = T::GetTypeID();

	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	
	ManagedTypeID managedTypeId = ntmip->GetManagedTypeID(nativeTypeId);
	ManagedObject* mo = ssl->CreateObject(managedTypeId);
	InstanceID managedInstanceId = mo->GetInstanceID();
	mo->SetFieldValue("m_instanceId", &managedInstanceId);

	NativeToManagedInstance ntmi(nativeInstanceId, mo->GetInstanceID());
	ntmip->CreateInstanceMapping(nativeTypeId, ntmi);

	return obj;
}

template<typename T>
static void RegisterType()
{
	TypeID typeId = T::GetTypeID();

	TypeNameMappings& tnm = TypeNameMappings::Instance();
	ScriptedTypeMap stm;
	stm.typeId = typeId;
	stm.createCallback = CreateInstance<T>;
	tnm.m_scriptedTypeMap.push_back(stm);
}

template<typename T>
static void RegisterManagedType(ManagedTypeID managedTypeId)
{
	TypeID typeId = T::GetTypeID();

	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ntmip->CreateTypeMapping(typeId, managedTypeId);

	TypeNameMappings& tnm = TypeNameMappings::Instance();
	ScriptedTypeMap stm;
	stm.typeId = typeId;
	stm.createCallback = CreateManagedInstance<T>;
	tnm.m_scriptedTypeMap.push_back(stm);
}
