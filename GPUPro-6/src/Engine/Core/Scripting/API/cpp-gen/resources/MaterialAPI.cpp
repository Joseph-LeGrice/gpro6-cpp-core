#include "stdafx.h"
#include "MaterialAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Material.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::MaterialAPI::RegisterCalls()
{
	mono_add_internal_call("Material::SetShaderIndex(int,int)", GPro::MaterialAPI::SetShaderIndex);
	mono_add_internal_call("Material::RegisterShaderResource(int,int,int)", GPro::MaterialAPI::RegisterShaderResource);
	mono_add_internal_call("Material::AddTextureSampler(int,int,int)", GPro::MaterialAPI::AddTextureSampler);
	mono_add_internal_call("Material::SetInteger(int,string,int)", GPro::MaterialAPI::SetInteger);
	mono_add_internal_call("Material::SetBoolean(int,string,bool)", GPro::MaterialAPI::SetBoolean);
	mono_add_internal_call("Material::SetFloat(int,string,float)", GPro::MaterialAPI::SetFloat);
	mono_add_internal_call("Material::SetFloat2(int,string,Vector2)", GPro::MaterialAPI::SetFloat2);
	mono_add_internal_call("Material::SetFloat3(int,string,Vector3)", GPro::MaterialAPI::SetFloat3);
	mono_add_internal_call("Material::SetFloat4(int,string,Vector4)", GPro::MaterialAPI::SetFloat4);
	mono_add_internal_call("Material::SetMatrix3x3(int,string,Matrix3x3)", GPro::MaterialAPI::SetMatrix3x3);
	mono_add_internal_call("Material::SetMatrix4x4(int,string,Matrix4x4)", GPro::MaterialAPI::SetMatrix4x4);
}

void GPro::MaterialAPI::SetShaderIndex(int managedInstanceId, int arg0)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetShaderIndex(arg0);
}

void GPro::MaterialAPI::RegisterShaderResource(int managedInstanceId, int arg0, int arg1)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->RegisterShaderResource(arg0, arg1);
}

void GPro::MaterialAPI::AddTextureSampler(int managedInstanceId, int arg0, int arg1)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->AddTextureSampler(arg0, arg1);
}

void GPro::MaterialAPI::SetInteger(int managedInstanceId, MonoString* arg0, int arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetInteger(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetBoolean(int managedInstanceId, MonoString* arg0, bool arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetBoolean(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetFloat(int managedInstanceId, MonoString* arg0, float arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetFloat(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetFloat2(int managedInstanceId, MonoString* arg0, Vector2 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetFloat2(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetFloat3(int managedInstanceId, MonoString* arg0, Vector3 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetFloat3(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetFloat4(int managedInstanceId, MonoString* arg0, Vector4 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetFloat4(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetMatrix3x3(int managedInstanceId, MonoString* arg0, Matrix3x3 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetMatrix3x3(arg0_marshalled, arg1);
}

void GPro::MaterialAPI::SetMatrix4x4(int managedInstanceId, MonoString* arg0, Matrix4x4 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Material::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Material* nativeClassInstance = tom->GetInstance<Material>(nativeInstanceId);
	nativeClassInstance->SetMatrix4x4(arg0_marshalled, arg1);
}
// ## Generated Code ##