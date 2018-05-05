#include "stdafx.h"
#include "TypedObjectManagerAPI.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"


std::wstring GetUTF16(MonoString* ms)
{
    mono_unichar2* pathStr = mono_string_to_utf16(ms);
    std::wstringstream ss;
    int i = 0;
    while (pathStr[i] != NULL)
    {
        ss << static_cast<wchar_t>(pathStr[i]);
        i++;
    }
    mono_free(static_cast<void*>(pathStr));
    return ss.str();
}

MonoObject* TypedObjectManagerAPI::Create(MonoString* className)
{
	const char* nativeTypeId = mono_string_to_utf8(className);

	TypedObjectManager* rm = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	ITypedObject* newInstance = rm->Create(nativeTypeId);
	InstanceID nativeObjectId = newInstance->GetInstanceID();

	NativeToManagedInstanceMap* n2m = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* managedObj = n2m->GetManagedObject(nativeTypeId, nativeObjectId);

	mono_free((void*)nativeTypeId);

	return managedObj->GetManagedObject();
}

void TypedObjectManagerAPI::RegisterMonoMethods()
{
	mono_add_internal_call("TypedObjectManager::Create", TypedObjectManagerAPI::Create);
	//mono_add_internal_call("TypedObjectManagerAPI::Delete", TypedObjectManagerAPI::Delete);
	//mono_add_internal_call("TypedObjectManagerAPI::GetAllResourcesOfType", TypedObjectManagerAPI::GetAllResourcesOfType);
	//mono_add_internal_call("TypedObjectManagerAPI::GetInstance", TypedObjectManagerAPI::GetInstance);
}
