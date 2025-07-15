#include "stdafx.h"
#include "MaterialAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Material.h"
#include "Engine/Core/DataStructures/MaterialPropertyList.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::MaterialAPI::RegisterCalls()
{
	mono_add_internal_call("Material::SetShader(int,ITypedObject)", GPro::MaterialAPI::SetShader);
	mono_add_internal_call("Material::RegisterShaderResource(int,ITypedObject,int)", GPro::MaterialAPI::RegisterShaderResource);
	mono_add_internal_call("Material::AddTextureSampler(int,ITypedObject,int)", GPro::MaterialAPI::AddTextureSampler);
	mono_add_internal_call("Material::InitProperties(int,PropertyInitializer[])", GPro::MaterialAPI::InitProperties);
	mono_add_internal_call("Material::SetInteger(int,string,int)", GPro::MaterialAPI::SetInteger);
	mono_add_internal_call("Material::SetBoolean(int,string,bool)", GPro::MaterialAPI::SetBoolean);
	mono_add_internal_call("Material::SetFloat(int,string,single)", GPro::MaterialAPI::SetFloat);
	mono_add_internal_call("Material::SetFloat2(int,string,Vector2)", GPro::MaterialAPI::SetFloat2);
	mono_add_internal_call("Material::SetFloat3(int,string,Vector3)", GPro::MaterialAPI::SetFloat3);
	mono_add_internal_call("Material::SetFloat4(int,string,Vector4)", GPro::MaterialAPI::SetFloat4);
	mono_add_internal_call("Material::SetMatrix3x3(int,string,Matrix3x3)", GPro::MaterialAPI::SetMatrix3x3);
	mono_add_internal_call("Material::SetMatrix4x4(int,string,Matrix4x4)", GPro::MaterialAPI::SetMatrix4x4);
	mono_add_internal_call("Material::SetCullState_Internal", GPro::MaterialAPI::SetCullState_Internal);
	mono_add_internal_call("Material::SetFillMode_Internal", GPro::MaterialAPI::SetFillMode_Internal);
	mono_add_internal_call("Material::SetColorBlending_Internal", GPro::MaterialAPI::SetColorBlending_Internal);
	mono_add_internal_call("Material::SetAlphaBlending_Internal", GPro::MaterialAPI::SetAlphaBlending_Internal);
}

extern void GPro::MaterialAPI::SetShader(InstanceID managedInstanceId, MonoObject* arg0)
{
	ToPtr arg0_marshalled = MonoMarshall::GetNativePointer(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetShader(arg0_marshalled);
}

extern void GPro::MaterialAPI::RegisterShaderResource(InstanceID managedInstanceId, MonoObject* arg0, int arg1)
{
	ToPtr arg0_marshalled = MonoMarshall::GetNativePointer(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->RegisterShaderResource(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::AddTextureSampler(InstanceID managedInstanceId, MonoObject* arg0, int arg1)
{
	ToPtr arg0_marshalled = MonoMarshall::GetNativePointer(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->AddTextureSampler(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::InitProperties(InstanceID managedInstanceId, MonoArray* arg0)
{
	std::vector<MaterialProperty::Initializer> arg0_marshalled = MonoMarshall::GetPropertyInitializerVector(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->InitProperties(arg0_marshalled);
}

extern void GPro::MaterialAPI::SetInteger(InstanceID managedInstanceId, MonoString* arg0, int arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetInteger(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetBoolean(InstanceID managedInstanceId, MonoString* arg0, bool arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetBoolean(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetFloat(InstanceID managedInstanceId, MonoString* arg0, float arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetFloat(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetFloat2(InstanceID managedInstanceId, MonoString* arg0, Vector2 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetFloat2(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetFloat3(InstanceID managedInstanceId, MonoString* arg0, Vector3 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetFloat3(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetFloat4(InstanceID managedInstanceId, MonoString* arg0, Vector4 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetFloat4(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetMatrix3x3(InstanceID managedInstanceId, MonoString* arg0, Matrix3x3 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetMatrix3x3(arg0_marshalled, arg1);
}

extern void GPro::MaterialAPI::SetMatrix4x4(InstanceID managedInstanceId, MonoString* arg0, Matrix4x4 arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetMatrix4x4(arg0_marshalled, arg1);
}

// ## Generated Code ##

extern void GPro::MaterialAPI::SetCullState_Internal(int managedInstanceId, int arg0)
{
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetCullState(static_cast<CullState>(arg0));
}

extern void GPro::MaterialAPI::SetFillMode_Internal(int managedInstanceId, int arg0)
{
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetFillMode(static_cast<FillMode>(arg0));
}

extern void GPro::MaterialAPI::SetColorBlending_Internal(int managedInstanceId, int arg0, int arg1, int arg2)
{
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetColorBlending(static_cast<BlendFactor>(arg0), static_cast<BlendFactor>(arg1), static_cast<BlendOperation>(arg2));
}

extern void GPro::MaterialAPI::SetAlphaBlending_Internal(int managedInstanceId, int arg0, int arg1, int arg2)
{
	Material* nativeClassInstance = MonoMarshall::GetNativeObject<Material>(managedInstanceId);
	nativeClassInstance->SetAlphaBlending(static_cast<BlendFactor>(arg0), static_cast<BlendFactor>(arg1), static_cast<BlendOperation>(arg2));
}