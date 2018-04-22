#pragma once

#include "ITypedObject.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"
#include "Engine/Core/Scripting/ManagedObject.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"

void CreateManagedCounterpart(ITypedObject* obj, const char* managedTypeName)
{
	ScriptedSystemLoader* ssl = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	ManagedObject* mo = ssl->CreateObject(managedTypeName);

	const char* nativeTypeName = obj->GetTypeName();
	TypeID nativeTypeId = TypeNameMappings::Instance().GetTypeID(nativeTypeName);
	InstanceID nativeInstanceId = obj->GetInstanceID();

	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	NativeToManagedObject ntmo(nativeTypeId, nativeInstanceId, mo->GetInstanceID());
	ntmip->CreateMapping(ntmo);
}