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
	mono_add_internal_call("MeshRenderer::Get_Mesh", GPro::MeshRendererAPI::Get_Mesh);
	mono_add_internal_call("MeshRenderer::Set_Mesh", GPro::MeshRendererAPI::Set_Mesh);
	mono_add_internal_call("MeshRenderer::Get_Material", GPro::MeshRendererAPI::Get_Material);
	mono_add_internal_call("MeshRenderer::Set_Material", GPro::MeshRendererAPI::Set_Material);
}

extern MonoObject* GPro::MeshRendererAPI::Get_Mesh(InstanceID managedInstanceId)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	return MonoMarshall::GetManagedObject(nativeClassInstance->m_mesh);
}

extern void GPro::MeshRendererAPI::Set_Mesh(InstanceID managedInstanceId, MonoObject* value)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	nativeClassInstance->m_mesh = MonoMarshall::GetNativePointer(value);
}

extern MonoObject* GPro::MeshRendererAPI::Get_Material(InstanceID managedInstanceId)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	return MonoMarshall::GetManagedObject(nativeClassInstance->m_material);
}

extern void GPro::MeshRendererAPI::Set_Material(InstanceID managedInstanceId, MonoObject* value)
{
	MeshRenderer* nativeClassInstance = MonoMarshall::GetNativeObject<MeshRenderer>(managedInstanceId);
	nativeClassInstance->m_material = MonoMarshall::GetNativePointer(value);
}

// ## Generated Code ##