#include "stdafx.h"
#include "TransformAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/Transform.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::TransformAPI::RegisterCalls()
{
	mono_add_internal_call("Transform::Get_position", GPro::TransformAPI::Get_position);
	mono_add_internal_call("Transform::Set_position", GPro::TransformAPI::Set_position);
	mono_add_internal_call("Transform::Get_scale", GPro::TransformAPI::Get_scale);
	mono_add_internal_call("Transform::Set_scale", GPro::TransformAPI::Set_scale);
	mono_add_internal_call("Transform::Get_rotation", GPro::TransformAPI::Get_rotation);
	mono_add_internal_call("Transform::Set_rotation", GPro::TransformAPI::Set_rotation);
}

extern Vector3 GPro::TransformAPI::Get_position(InstanceID managedInstanceId)
{
	Transform* nativeClassInstance = MonoMarshall::GetNativeObject<Transform>(managedInstanceId);
	return nativeClassInstance->m_position;
}

extern void GPro::TransformAPI::Set_position(InstanceID managedInstanceId, Vector3 value)
{
	Transform* nativeClassInstance = MonoMarshall::GetNativeObject<Transform>(managedInstanceId);
	nativeClassInstance->m_position = value;
}

extern Vector3 GPro::TransformAPI::Get_scale(InstanceID managedInstanceId)
{
	Transform* nativeClassInstance = MonoMarshall::GetNativeObject<Transform>(managedInstanceId);
	return nativeClassInstance->m_scale;
}

extern void GPro::TransformAPI::Set_scale(InstanceID managedInstanceId, Vector3 value)
{
	Transform* nativeClassInstance = MonoMarshall::GetNativeObject<Transform>(managedInstanceId);
	nativeClassInstance->m_scale = value;
}

extern Quaternion GPro::TransformAPI::Get_rotation(InstanceID managedInstanceId)
{
	Transform* nativeClassInstance = MonoMarshall::GetNativeObject<Transform>(managedInstanceId);
	return nativeClassInstance->m_rotation;
}

extern void GPro::TransformAPI::Set_rotation(InstanceID managedInstanceId, Quaternion value)
{
	Transform* nativeClassInstance = MonoMarshall::GetNativeObject<Transform>(managedInstanceId);
	nativeClassInstance->m_rotation = value;
}

// ## Generated Code ##