#include "stdafx.h"
#include "Texture2DArrayAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Texture2DArray.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::Texture2DArrayAPI::RegisterCalls()
{
	mono_add_internal_call("Texture2DArray::InitializeWithBitmaps(int,string[])", GPro::Texture2DArrayAPI::InitializeWithBitmaps);
	mono_add_internal_call("Texture2DArray::GetResourceViewID(int)", GPro::Texture2DArrayAPI::GetResourceViewID);
}

extern void GPro::Texture2DArrayAPI::InitializeWithBitmaps(int managedInstanceId, MonoArray* arg0)
{
	std::vector<std::wstring> arg0_marshalled = MonoMarshall::GetStringVector(arg0);
	Texture2DArray* nativeClassInstance = MonoMarshall::GetNativeObject<Texture2DArray>(managedInstanceId);
	nativeClassInstance->InitializeWithBitmaps(arg0_marshalled);
}

extern int GPro::Texture2DArrayAPI::GetResourceViewID(int managedInstanceId)
{
	Texture2DArray* nativeClassInstance = MonoMarshall::GetNativeObject<Texture2DArray>(managedInstanceId);
	return nativeClassInstance->GetResourceViewID();
}
// ## Generated Code ##