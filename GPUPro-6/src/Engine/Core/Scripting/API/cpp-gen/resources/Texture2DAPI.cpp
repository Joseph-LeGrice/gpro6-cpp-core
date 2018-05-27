#include "stdafx.h"
#include "Texture2DAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::Texture2DAPI::RegisterCalls()
{
	mono_add_internal_call("Texture2D::InitializeWithBitmap(int,string)", GPro::Texture2DAPI::InitializeWithBitmap);
	mono_add_internal_call("Texture2D::GetResourceViewID(int)", GPro::Texture2DAPI::GetResourceViewID);
}

extern void GPro::Texture2DAPI::InitializeWithBitmap(InstanceID managedInstanceId, MonoString* arg0)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Texture2D* nativeClassInstance = MonoMarshall::GetNativeObject<Texture2D>(managedInstanceId);
	nativeClassInstance->InitializeWithBitmap(arg0_marshalled);
}

extern int GPro::Texture2DAPI::GetResourceViewID(InstanceID managedInstanceId)
{
	Texture2D* nativeClassInstance = MonoMarshall::GetNativeObject<Texture2D>(managedInstanceId);
	return nativeClassInstance->GetResourceViewID();
}
// ## Generated Code ##