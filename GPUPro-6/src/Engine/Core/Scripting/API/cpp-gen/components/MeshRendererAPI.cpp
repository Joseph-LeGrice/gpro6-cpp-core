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

extern int GPro::MeshRendererAPI::Get_MeshIndex(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(MeshRenderer::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	MeshRenderer* nativeClassInstance = tom->GetInstance<MeshRenderer>(nativeInstanceId);
	return nativeClassInstance->m_meshIndex;
}

extern void GPro::MeshRendererAPI::Set_MeshIndex(int managedInstanceId, int value)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(MeshRenderer::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	MeshRenderer* nativeClassInstance = tom->GetInstance<MeshRenderer>(nativeInstanceId);
	nativeClassInstance->m_meshIndex = value;
}

extern int GPro::MeshRendererAPI::Get_MaterialIndex(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(MeshRenderer::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	MeshRenderer* nativeClassInstance = tom->GetInstance<MeshRenderer>(nativeInstanceId);
	return nativeClassInstance->m_materialIndex;
}

extern void GPro::MeshRendererAPI::Set_MaterialIndex(int managedInstanceId, int value)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(MeshRenderer::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	MeshRenderer* nativeClassInstance = tom->GetInstance<MeshRenderer>(nativeInstanceId);
	nativeClassInstance->m_materialIndex = value;
}

// ## Generated Code ##