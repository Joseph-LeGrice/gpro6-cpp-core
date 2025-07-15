#include "stdafx.h"
#include "TypedObjectManagerAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"

// ## Generated Code ##
extern void GPro::TypedObjectManagerAPI::RegisterCalls()
{
	mono_add_internal_call("TypedObjectManager::Create", GPro::TypedObjectManagerAPI::Create);
	mono_add_internal_call("TypedObjectManager::GetInstance", GPro::TypedObjectManagerAPI::GetInstance);
}


// ## Generated Code ##

extern MonoObject* GPro::TypedObjectManagerAPI::Create(MonoString* arg0)
{
	const char* nativeTypeId = mono_string_to_utf8(arg0);

	TypedObjectManager* rm = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	ITypedObject* newInstance = rm->Create(nativeTypeId);
	InstanceID nativeObjectId = newInstance->GetInstanceID();

	NativeToManagedInstanceMap* n2m = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* managedObj = n2m->GetManagedObject(nativeTypeId, nativeObjectId);

	mono_free((void*)nativeTypeId);

	return managedObj->GetManagedObject();
}

extern MonoObject* GPro::TypedObjectManagerAPI::GetInstance(MonoString* arg0, int arg1)
{
	const char* nativeTypeId = mono_string_to_utf8(arg0);

	NativeToManagedInstanceMap* n2m = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* managedObj = n2m->GetManagedObject(nativeTypeId, arg1);
	return managedObj->GetManagedObject();
}
