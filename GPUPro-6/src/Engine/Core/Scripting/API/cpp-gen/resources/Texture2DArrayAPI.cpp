#include "stdafx.h"
#include "Texture2DArrayAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Texture2DArray.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::Texture2DArrayAPI::RegisterCalls()
{
	mono_add_internal_call("Texture2DArray::InitializeWithBitmaps(int,System.Collections.Generic.List<string>)", GPro::Texture2DArrayAPI::InitializeWithBitmaps);
	mono_add_internal_call("Texture2DArray::GetResourceViewID(int)", GPro::Texture2DArrayAPI::GetResourceViewID);
}

void GPro::Texture2DArrayAPI::InitializeWithBitmaps(int managedInstanceId, MonoArray* arg0)
{
	std::vector<std::wstring> arg0_marshalled = MonoMarshall::GetStringVector(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Texture2DArray::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2DArray* nativeClassInstance = tom->GetInstance<Texture2DArray>(nativeInstanceId);
	nativeClassInstance->InitializeWithBitmaps(arg0_marshalled);
}

int GPro::Texture2DArrayAPI::GetResourceViewID(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Texture2DArray::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2DArray* nativeClassInstance = tom->GetInstance<Texture2DArray>(nativeInstanceId);
	return nativeClassInstance->GetResourceViewID();
}
// ## Generated Code ##