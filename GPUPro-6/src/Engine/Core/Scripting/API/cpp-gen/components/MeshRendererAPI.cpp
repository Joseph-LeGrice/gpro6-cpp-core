#include "stdafx.h"
#include "MeshRendererAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/MeshRenderer.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::MeshRendererAPI::RegisterCalls()
{
	mono_add_internal_call("MeshRenderer::Get_MeshIndex", GPro::MeshRendererAPI::Get_MeshIndex);
	mono_add_internal_call("MeshRenderer::Set_MeshIndex", GPro::MeshRendererAPI::Set_MeshIndex);
	mono_add_internal_call("MeshRenderer::Get_MaterialIndex", GPro::MeshRendererAPI::Get_MaterialIndex);
	mono_add_internal_call("MeshRenderer::Set_MaterialIndex", GPro::MeshRendererAPI::Set_MaterialIndex);
}

extern int GPro::MeshRendererAPI::Get_MeshIndex(InstanceID managedInstanceId)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	return nativeClassInstance->m_meshIndex;
}

extern void GPro::MeshRendererAPI::Set_MeshIndex(InstanceID managedInstanceId, int value)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	nativeClassInstance->m_meshIndex = value;
}

extern int GPro::MeshRendererAPI::Get_MaterialIndex(InstanceID managedInstanceId)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	return nativeClassInstance->m_materialIndex;
}

extern void GPro::MeshRendererAPI::Set_MaterialIndex(InstanceID managedInstanceId, int value)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	nativeClassInstance->m_materialIndex = value;
}

// ## Generated Code ##