#include "stdafx.h"
#include "ShaderAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/Shader.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::ShaderAPI::RegisterCalls()
{
	mono_add_internal_call("Shader::InitVertexShader(int,string,string)", GPro::ShaderAPI::InitVertexShader);
	mono_add_internal_call("Shader::InitPixelShader(int,string,string)", GPro::ShaderAPI::InitPixelShader);
	mono_add_internal_call("Shader::InitGeometryShader(int,string,string)", GPro::ShaderAPI::InitGeometryShader);
	mono_add_internal_call("Shader::InitHullShader(int,string,string)", GPro::ShaderAPI::InitHullShader);
	mono_add_internal_call("Shader::InitDomainShader(int,string,string)", GPro::ShaderAPI::InitDomainShader);
}

void GPro::ShaderAPI::InitVertexShader(int managedInstanceId, MonoString* arg0, MonoString* arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	std::wstring arg1_marshalled = MonoMarshall::GetUTF16String(arg1);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Shader::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Shader* nativeClassInstance = tom->GetInstance<Shader>(nativeInstanceId);
	nativeClassInstance->InitVertexShader(arg0_marshalled, arg1_marshalled);
}

void GPro::ShaderAPI::InitPixelShader(int managedInstanceId, MonoString* arg0, MonoString* arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	std::wstring arg1_marshalled = MonoMarshall::GetUTF16String(arg1);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Shader::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Shader* nativeClassInstance = tom->GetInstance<Shader>(nativeInstanceId);
	nativeClassInstance->InitPixelShader(arg0_marshalled, arg1_marshalled);
}

void GPro::ShaderAPI::InitGeometryShader(int managedInstanceId, MonoString* arg0, MonoString* arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	std::wstring arg1_marshalled = MonoMarshall::GetUTF16String(arg1);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Shader::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Shader* nativeClassInstance = tom->GetInstance<Shader>(nativeInstanceId);
	nativeClassInstance->InitGeometryShader(arg0_marshalled, arg1_marshalled);
}

void GPro::ShaderAPI::InitHullShader(int managedInstanceId, MonoString* arg0, MonoString* arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	std::wstring arg1_marshalled = MonoMarshall::GetUTF16String(arg1);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Shader::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Shader* nativeClassInstance = tom->GetInstance<Shader>(nativeInstanceId);
	nativeClassInstance->InitHullShader(arg0_marshalled, arg1_marshalled);
}

void GPro::ShaderAPI::InitDomainShader(int managedInstanceId, MonoString* arg0, MonoString* arg1)
{
	std::wstring arg0_marshalled = MonoMarshall::GetUTF16String(arg0);
	std::wstring arg1_marshalled = MonoMarshall::GetUTF16String(arg1);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Shader::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Shader* nativeClassInstance = tom->GetInstance<Shader>(nativeInstanceId);
	nativeClassInstance->InitDomainShader(arg0_marshalled, arg1_marshalled);
}
// ## Generated Code ##