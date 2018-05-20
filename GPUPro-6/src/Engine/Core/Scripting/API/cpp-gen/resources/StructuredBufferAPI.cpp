#include "stdafx.h"
#include "StructuredBufferAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/StructuredBuffer.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::StructuredBufferAPI::RegisterCalls()
{
	mono_add_internal_call("StructuredBuffer::GetMyResourceViewID(int)", GPro::StructuredBufferAPI::GetMyResourceViewID);
}

int GPro::StructuredBufferAPI::GetMyResourceViewID(int managedInstanceId)
{
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	InstanceID nativeInstanceId = ntmip->GetNativeInstanceID(StructuredBuffer::GetTypeID(), managedInstanceId);
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	StructuredBuffer* nativeClassInstance = tom->GetInstance<StructuredBuffer>(nativeInstanceId);
	return nativeClassInstance->GetMyResourceViewID();
}
// ## Generated Code ##