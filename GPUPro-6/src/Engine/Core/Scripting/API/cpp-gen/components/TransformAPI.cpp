#include "stdafx.h"
#include "TransformAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/Transform.h"

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

MonoObject* GPro::TransformAPI::Get_position(int managedInstanceId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(managedInstanceId);
	return MonoMarshall::GetManagedVector3(nativeClassInstance->m_position);
}

void GPro::TransformAPI::Set_position(int managedInstanceId, MonoObject* value)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(managedInstanceId);
	nativeClassInstance->m_position = MonoMarshall::GetVector3(value);
}

MonoObject* GPro::TransformAPI::Get_scale(int managedInstanceId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(managedInstanceId);
	return MonoMarshall::GetManagedVector3(nativeClassInstance->m_scale);
}

void GPro::TransformAPI::Set_scale(int managedInstanceId, MonoObject* value)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(managedInstanceId);
	nativeClassInstance->m_scale = MonoMarshall::GetVector3(value);
}

MonoObject* GPro::TransformAPI::Get_rotation(int managedInstanceId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(managedInstanceId);
	return MonoMarshall::GetManagedQuaternion(nativeClassInstance->m_rotation);
}

void GPro::TransformAPI::Set_rotation(int managedInstanceId, MonoObject* value)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Transform* nativeClassInstance = tom->GetInstance<Transform>(managedInstanceId);
	nativeClassInstance->m_rotation = MonoMarshall::GetQuaternion(value);
}

// ## Generated Code ##