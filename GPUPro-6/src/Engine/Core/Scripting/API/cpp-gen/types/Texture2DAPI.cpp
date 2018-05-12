#include "stdafx.h"
#include "Texture2DAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::Texture2DAPI::RegisterCalls()
{
	mono_add_internal_call("Texture2D::InitializeWithBitmap(int,string)", GPro::Texture2DAPI::InitializeWithBitmap);
}

void GPro::Texture2DAPI::InitializeWithBitmap(int managedInstanceId, const wchar_t* arg0)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2D* nativeClassInstance = tom->GetInstance<Texture2D>(managedInstanceId);
	nativeClassInstance->InitializeWithBitmap(arg0);
}
// ## Generated Code ##