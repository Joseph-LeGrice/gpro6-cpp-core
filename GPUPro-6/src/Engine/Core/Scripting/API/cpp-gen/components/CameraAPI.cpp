#include "stdafx.h"
#include "CameraAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Components/Camera.h"

#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::CameraAPI::RegisterCalls()
{
	mono_add_internal_call("Camera::SetOrthographic(int,single,single,single)", GPro::CameraAPI::SetOrthographic);
	mono_add_internal_call("Camera::SetPerspective(int,single,single,single,single)", GPro::CameraAPI::SetPerspective);
}

extern void GPro::CameraAPI::SetOrthographic(InstanceID managedInstanceId, float arg0, float arg1, float arg2)
{
	Camera* nativeClassInstance = MonoMarshall::GetNativeObject<Camera>(managedInstanceId);
	nativeClassInstance->SetOrthographic(arg0, arg1, arg2);
}

extern void GPro::CameraAPI::SetPerspective(InstanceID managedInstanceId, float arg0, float arg1, float arg2, float arg3)
{
	Camera* nativeClassInstance = MonoMarshall::GetNativeObject<Camera>(managedInstanceId);
	nativeClassInstance->SetPerspective(arg0, arg1, arg2, arg3);
}
// ## Generated Code ##