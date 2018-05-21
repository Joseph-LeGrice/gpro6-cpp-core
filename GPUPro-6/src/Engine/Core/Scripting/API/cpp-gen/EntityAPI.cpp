#include "stdafx.h"
#include "EntityAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::EntityAPI::RegisterCalls()
{
	mono_add_internal_call("Entity::AddComponentInternal", GPro::EntityAPI::AddComponentInternal);
	mono_add_internal_call("Entity::RemoveComponentInternal", GPro::EntityAPI::RemoveComponentInternal);
	mono_add_internal_call("Entity::GetComponentInternal", GPro::EntityAPI::GetComponentInternal);
}


// ## Generated Code ##