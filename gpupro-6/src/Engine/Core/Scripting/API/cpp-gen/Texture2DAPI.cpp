#include "stdafx.h"
#include "Texture2DAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"

void Texture2DAPI::RegisterCalls()
{
	mono_add_internal_call("Texture2D::InitializeWithBitmap(int managedInstanceId, string arg0)", Texture2DAPI::InitializeWithBitmap);
}

void Texture2DAPI::InitializeWithBitmap(int managedInstanceId, const wchar_t* arg0)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Texture2D* nativeClassInstance = tom->GetInstance<Texture2D>(managedInstanceId);
	nativeClassInstance->InitializeWithBitmap(arg0);
}