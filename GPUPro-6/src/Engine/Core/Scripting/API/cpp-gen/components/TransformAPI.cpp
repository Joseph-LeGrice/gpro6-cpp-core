#include "stdafx.h"
#include "TransformAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/Transform.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::TransformAPI::RegisterCalls()
{
	mono_add_internal_call("Transform::Get_position", GPro::TransformAPI::Get_position);
	mono_add_internal_call("Transform::Set_position", GPro::TransformAPI::Set_position);
	mono_add_internal_call("Transform::Get_scale", GPro::TransformAPI::Get_scale);
	mono_add_internal_call("Transform::Set_scale", GPro::TransformAPI::Set_scale);
	mono_add_internal_call("Transform::Get_rotation", GPro::TransformAPI::Get_rotation);
	mono_add_internal_call("Transform::Set_rotation", GPro::TransformAPI::Set_rotation);
}

Vector3 GPro::TransformAPI::Get_position(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Transform::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(nativeInstanceId);
	return nativeClassInstance->m_position;
}

void GPro::TransformAPI::Set_position(int managedInstanceId, Vector3 value)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Transform::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(nativeInstanceId);
	nativeClassInstance->m_position = value;
}

Vector3 GPro::TransformAPI::Get_scale(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Transform::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(nativeInstanceId);
	return nativeClassInstance->m_scale;
}

void GPro::TransformAPI::Set_scale(int managedInstanceId, Vector3 value)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Transform::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(nativeInstanceId);
	nativeClassInstance->m_scale = value;
}

Quaternion GPro::TransformAPI::Get_rotation(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Transform::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(nativeInstanceId);
	return nativeClassInstance->m_rotation;
}

void GPro::TransformAPI::Set_rotation(int managedInstanceId, Quaternion value)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Transform::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(nativeInstanceId);
	nativeClassInstance->m_rotation = value;
}

// ## Generated Code ##