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
	mono_add_internal_call("StructuredBuffer::GetResourceView(int)", GPro::StructuredBufferAPI::GetResourceView);
}

extern MonoObject* GPro::StructuredBufferAPI::GetResourceView(InstanceID managedInstanceId)
{
	StructuredBuffer* nativeClassInstance = MonoMarshall::GetNativeObject<StructuredBuffer>(managedInstanceId);
	return MonoMarshall::GetManagedObject(nativeClassInstance->GetResourceView());
}
// ## Generated Code ##