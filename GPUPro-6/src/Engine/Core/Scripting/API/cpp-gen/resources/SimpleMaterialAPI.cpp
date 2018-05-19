#include "stdafx.h"
#include "SimpleMaterialAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Material/SimpleMaterial.h"

#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::SimpleMaterialAPI::RegisterCalls()
{
	mono_add_internal_call("SimpleMaterial::SetShaderIndex(int,int)", GPro::SimpleMaterialAPI::SetShaderIndex);
	mono_add_internal_call("SimpleMaterial::RegisterShaderResource(int,int,int)", GPro::SimpleMaterialAPI::RegisterShaderResource);
}

void GPro::SimpleMaterialAPI::SetShaderIndex(int managedInstanceId, int arg0)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	SimpleMaterial* nativeClassInstance = tom->GetInstance<SimpleMaterial>(managedInstanceId);
	nativeClassInstance->SetShaderIndex(arg0);
}

void GPro::SimpleMaterialAPI::RegisterShaderResource(int managedInstanceId, int arg0, int arg1)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	SimpleMaterial* nativeClassInstance = tom->GetInstance<SimpleMaterial>(managedInstanceId);
	nativeClassInstance->RegisterShaderResource(arg0, arg1);
}
// ## Generated Code ##