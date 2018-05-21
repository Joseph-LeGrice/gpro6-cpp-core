#include "stdafx.h"
#include "ScriptedSystemInterfaceAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Scripting/ScriptedSystem.h"
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"
#include "Engine/Core/SystemManagement/SystemContainer.h"

// ## Generated Code ##
extern void GPro::ScriptedSystemInterfaceAPI::RegisterCalls()
{
	mono_add_internal_call("ScriptedSystemInterface::RegisterSystemInstance", GPro::ScriptedSystemInterfaceAPI::RegisterSystemInstance);
}


// ## Generated Code ##

void GPro::ScriptedSystemInterfaceAPI::RegisterSystemInstance(MonoObject* arg0)
{
	ScriptedSystem* newSystem = new ScriptedSystem(arg0);
	SystemContainer* sysContainer = GlobalStaticReferences::Instance()->GetSystemContainer();
	sysContainer->RegisterSystem(newSystem);
	ScriptedSystemLoader* systemLoader = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	systemLoader->RegisterSubsystem(newSystem);
}
