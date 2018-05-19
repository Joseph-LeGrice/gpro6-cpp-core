#include "stdafx.h"
#include "MaterialAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Material.h"

#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::MaterialAPI::RegisterCalls()
{
	mono_add_internal_call("Material::SetShaderIndex(int,int)", GPro::MaterialAPI::SetShaderIndex);
	mono_add_internal_call("Material::RegisterShaderResource(int,int,int)", GPro::MaterialAPI::RegisterShaderResource);
}

void GPro::MaterialAPI::SetShaderIndex(int managedInstanceId, int arg0)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(managedInstanceId);
	nativeClassInstance->SetShaderIndex(arg0);
}

void GPro::MaterialAPI::RegisterShaderResource(int managedInstanceId, int arg0, int arg1)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(managedInstanceId);
	nativeClassInstance->RegisterShaderResource(arg0, arg1);
}
// ## Generated Code ##