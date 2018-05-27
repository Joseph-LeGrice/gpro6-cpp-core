#include "stdafx.h"
#include "StructuredBufferAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/StructuredBuffer.h"

#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::StructuredBufferAPI::RegisterCalls()
{
	mono_add_internal_call("StructuredBuffer::GetMyResourceViewID(int)", GPro::StructuredBufferAPI::GetMyResourceViewID);
}

extern int GPro::StructuredBufferAPI::GetMyResourceViewID(InstanceID managedInstanceId)
{
	StructuredBuffer* nativeClassInstance = MonoMarshall::GetNativeObject<StructuredBuffer>(managedInstanceId);
	return nativeClassInstance->GetMyResourceViewID();
}
// ## Generated Code ##