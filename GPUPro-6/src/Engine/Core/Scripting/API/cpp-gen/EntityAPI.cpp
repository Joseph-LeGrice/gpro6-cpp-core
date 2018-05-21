#include "stdafx.h"
#include "EntityAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"

// ## Generated Code ##
extern void GPro::EntityAPI::RegisterCalls()
{
	mono_add_internal_call("Entity::AddComponentInternal", GPro::EntityAPI::AddComponentInternal);
	mono_add_internal_call("Entity::RemoveComponentInternal", GPro::EntityAPI::RemoveComponentInternal);
	mono_add_internal_call("Entity::GetComponentInternal", GPro::EntityAPI::GetComponentInternal);
}


// ## Generated Code ##

extern MonoObject* GPro::EntityAPI::AddComponentInternal(int managedEntityInstanceId, MonoString* monoManagedComponentTypeId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeEntityInstanceId = ntmip->GetNativeInstanceID(Entity::GetTypeID(), managedEntityInstanceId);

	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Entity* nativeEntityInstance = tom->GetInstance<Entity>(nativeEntityInstanceId);

	ManagedTypeID managedComponentTypeId = MonoMarshall::GetUTF8String(monoManagedComponentTypeId);
	TypeID nativeComponentTypeId = ntmip->GetNativeTypeID(managedComponentTypeId);

	IComponent* newComponentInstance = nativeEntityInstance->AddComponent(nativeComponentTypeId);
	ManagedObject* managedComponent = ntmip->GetManagedObject(nativeComponentTypeId, newComponentInstance->GetInstanceID());
	return managedComponent->GetManagedObject();
}

extern void GPro::EntityAPI::RemoveComponentInternal(int managedEntityInstanceId, MonoString* monoManagedComponentTypeId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeEntityInstanceId = ntmip->GetNativeInstanceID(Entity::GetTypeID(), managedEntityInstanceId);
	
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Entity* nativeEntityInstance = tom->GetInstance<Entity>(nativeEntityInstanceId);

	ManagedTypeID managedComponentTypeId = MonoMarshall::GetUTF8String(monoManagedComponentTypeId);
	TypeID nativeComponentTypeId = ntmip->GetNativeTypeID(managedComponentTypeId);

	nativeEntityInstance->RemoveComponent(nativeComponentTypeId);
}

extern MonoObject* GPro::EntityAPI::GetComponentInternal(int managedEntityInstanceId, MonoString* monoManagedComponentTypeId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeEntityInstanceId = ntmip->GetNativeInstanceID(Entity::GetTypeID(), managedEntityInstanceId);

	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Entity* nativeEntityInstance = tom->GetInstance<Entity>(nativeEntityInstanceId);

	ManagedTypeID managedComponentTypeId = MonoMarshall::GetUTF8String(monoManagedComponentTypeId);
	TypeID nativeComponentTypeId = ntmip->GetNativeTypeID(managedComponentTypeId);

	IComponent* componentInstance = nativeEntityInstance->GetComponent(nativeComponentTypeId);
	if (componentInstance != nullptr)
	{
		ManagedObject* managedComponent = ntmip->GetManagedObject(nativeComponentTypeId, componentInstance->GetInstanceID());
		return managedComponent->GetManagedObject();
	}
	else
	{
		return nullptr;
	}
}
