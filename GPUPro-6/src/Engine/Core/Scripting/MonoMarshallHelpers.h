#pragma once

#include <vector>
#include "Engine/Core/RTTI/RTTI.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#include <mono/metadata/metadata.h>
#pragma warning(pop)

namespace MonoMarshall
{
	extern std::string GetUTF8String(MonoString* ms);
	extern std::wstring GetUTF16String(MonoString* ms);
	
	extern std::vector<std::wstring> GetStringVector(MonoArray* ma);

	extern ToPtr GetNativePointer(MonoObject* obj);
	extern MonoObject* GetManagedObject(ToPtr obj);

	template<class T>
	T* GetNativeObject(InstanceID managedInstanceId)
	{
		InstanceID nativeInstanceId = GetNativeInstanceID<T>(managedInstanceId);
		TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
		return tom->GetInstance<T>(nativeInstanceId);
	}

	template<class T>
	InstanceID GetNativeInstanceID(InstanceID managedInstanceId)
	{
		T temp;
		NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
		return ntmip->GetNativeInstanceID(temp.GetTypeID(), managedInstanceId);
	}
}