#include "stdafx.h"
#include "LightAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/Light.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::LightAPI::RegisterCalls()
{
	mono_add_internal_call("Light::Get_Range", GPro::LightAPI::Get_Range);
	mono_add_internal_call("Light::Set_Range", GPro::LightAPI::Set_Range);
}

float GPro::LightAPI::Get_Range(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Light::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Light* nativeClassInstance = tom->GetInstance<Light>(nativeInstanceId);
	return nativeClassInstance->m_range;
}

void GPro::LightAPI::Set_Range(int managedInstanceId, float value)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(Light::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Light* nativeClassInstance = tom->GetInstance<Light>(nativeInstanceId);
	nativeClassInstance->m_range = value;
}

// ## Generated Code ##