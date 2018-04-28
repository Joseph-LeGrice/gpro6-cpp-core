#pragma once

#include "TypeNameMapping.h"
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"

extern void RegisterAllTypes();

template<class T>
ITypedObject* CreateInstance()
{
	return new T();
}

template<class T>
ITypedObject* CreateManagedInstance()
{
	T* obj = new T();
	TypeID nativeTypeId = obj->GetTypeName();
	InstanceID nativeInstanceId = obj->GetInstanceID();

	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	
	ManagedTypeID managedTypeId = ntmip->GetManagedTypeID(nativeTypeId);
	ManagedObject* mo = ssl->CreateObject(managedTypeId);
	mo->SetFieldValue("m_instanceId", &nativeInstanceId);

	NativeToManagedInstance ntmi(nativeInstanceId, mo->GetInstanceID());
	ntmip->CreateInstanceMapping(nativeTypeId, ntmi);

	return obj;
}

template<typename T>
static void RegisterType()
{
	T proto;
	TypeID typeId = proto.GetTypeName();

	TypeNameMappings& tnm = TypeNameMappings::Instance();
	ScriptedTypeMap stm;
	stm.typeId = typeId;
	stm.createCallback = CreateInstance<T>;
	tnm.m_scriptedTypeMap.push_back(stm);
}

template<typename T>
static void RegisterManagedType(ManagedTypeID managedTypeId)
{
	T proto;
	TypeID typeId = proto.GetTypeName();

	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ntmip->CreateTypeMapping(typeId, managedTypeId);

	TypeNameMappings& tnm = TypeNameMappings::Instance();
	ScriptedTypeMap stm;
	stm.typeId = typeId;
	stm.createCallback = CreateManagedInstance<T>;
	tnm.m_scriptedTypeMap.push_back(stm);
}
