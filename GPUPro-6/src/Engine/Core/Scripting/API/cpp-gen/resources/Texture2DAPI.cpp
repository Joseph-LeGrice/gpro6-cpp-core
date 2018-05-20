#include "stdafx.h"
#include "Texture2DAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::Texture2DAPI::RegisterCalls()
{
	mono_add_internal_call("Texture2D::InitializeWithBitmap(int,string)", GPro::Texture2DAPI::InitializeWithBitmap);
	mono_add_internal_call("Texture2D::GetResourceViewID(int)", GPro::Texture2DAPI::GetResourceViewID);
}

void GPro::Texture2DAPI::InitializeWithBitmap(int managedInstanceId, MonoString* arg0)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Texture2D::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2D* nativeClassInstance = tom->GetInstance<Texture2D>(nativeInstanceId);
	nativeClassInstance->InitializeWithBitmap(arg0_marshalled);
}

int GPro::Texture2DAPI::GetResourceViewID(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Texture2D::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2D* nativeClassInstance = tom->GetInstance<Texture2D>(nativeInstanceId);
	return nativeClassInstance->GetResourceViewID();
}
// ## Generated Code ##