#include "stdafx.h"
#include "ApplicationAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Application/Application.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)


// ## Generated Code ##
extern void GPro::ApplicationAPI::RegisterCalls()
{
	mono_add_internal_call("Application::GetInstallLocation", GPro::ApplicationAPI::GetInstallLocation);
}


// ## Generated Code ##

extern MonoString* GPro::ApplicationAPI::GetInstallLocation()
{
    std::wstring result = Application::GetInstallLocation();
    return MonoMarshall::GetMonoString(result.c_str());
}
