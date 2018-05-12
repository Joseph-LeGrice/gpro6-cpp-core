#include "stdafx.h"
#include "StructuredBufferAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceTypes/StructuredBuffer.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
void GPro::StructuredBufferAPI::RegisterCalls()
{
	mono_add_internal_call("StructuredBuffer::GetMyResourceViewID(int,)", GPro::StructuredBufferAPI::GetMyResourceViewID);
}

int GPro::StructuredBufferAPI::GetMyResourceViewID(int managedInstanceId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	StructuredBuffer* nativeClassInstance = tom->GetInstance<StructuredBuffer>(managedInstanceId);
	return nativeClassInstance->GetMyResourceViewID();
}
// ## Generated Code ##