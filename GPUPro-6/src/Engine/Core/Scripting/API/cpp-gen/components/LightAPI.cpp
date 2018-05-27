#include "stdafx.h"
#include "LightAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/Light.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::LightAPI::RegisterCalls()
{
	mono_add_internal_call("Light::Get_Range", GPro::LightAPI::Get_Range);
	mono_add_internal_call("Light::Set_Range", GPro::LightAPI::Set_Range);
}

extern float GPro::LightAPI::Get_Range(InstanceID managedInstanceId)
{
	Light* nativeClassInstance = MonoMarshall::GetNativeObject<Light>(managedInstanceId);
	return nativeClassInstance->m_range;
}

extern void GPro::LightAPI::Set_Range(InstanceID managedInstanceId, float value)
{
	Light* nativeClassInstance = MonoMarshall::GetNativeObject<Light>(managedInstanceId);
	nativeClassInstance->m_range = value;
}

// ## Generated Code ##