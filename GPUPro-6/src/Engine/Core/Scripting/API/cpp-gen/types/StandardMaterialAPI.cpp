#include "stdafx.h"
#include "StandardMaterialAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Material/StandardMaterial.hpp"

#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::StandardMaterialAPI::RegisterCalls()
{
	mono_add_internal_call("StandardMaterial::SetShaderIndex(int,int)", GPro::StandardMaterialAPI::SetShaderIndex);
	mono_add_internal_call("StandardMaterial::RegisterShaderResource(int,int,int)", GPro::StandardMaterialAPI::RegisterShaderResource);
}

void GPro::StandardMaterialAPI::SetShaderIndex(int managedInstanceId, int arg0)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	StandardMaterial* nativeClassInstance = tom->GetInstance<StandardMaterial>(managedInstanceId);
	nativeClassInstance->SetShaderIndex(arg0);
}

void GPro::StandardMaterialAPI::RegisterShaderResource(int managedInstanceId, int arg0, int arg1)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	StandardMaterial* nativeClassInstance = tom->GetInstance<StandardMaterial>(managedInstanceId);
	nativeClassInstance->RegisterShaderResource(arg0, arg1);
}
// ## Generated Code ##