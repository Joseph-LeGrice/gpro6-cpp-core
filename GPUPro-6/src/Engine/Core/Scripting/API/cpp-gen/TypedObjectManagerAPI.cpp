#include "stdafx.h"
#include "TypedObjectManagerAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"


//std::wstring GetUTF16(MonoString* ms)
//{
//    mono_unichar2* pathStr = mono_string_to_utf16(ms);
//    std::wstringstream ss;
//    int i = 0;
//    while (pathStr[i] != NULL)
//    {
//        ss << static_cast<wchar_t>(pathStr[i]);
//        i++;
//    }
//    mono_free(static_cast<void*>(pathStr));
//    return ss.str();
//}

void GPro::TypedObjectManagerAPI::RegisterCalls()
{
	mono_add_internal_call("TypedObjectManager::Create", GPro::TypedObjectManagerAPI::Create);
}

MonoObject* GPro::TypedObjectManagerAPI::Create(MonoString* arg0)
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