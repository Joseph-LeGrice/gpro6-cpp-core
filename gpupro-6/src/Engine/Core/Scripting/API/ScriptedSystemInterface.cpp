#include "stdafx.h"
#include "ScriptedSystemInterface.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Scripting/ScriptedSystem.h"
#include "Engine/Core/Scripting/ScriptedSystemLoader.h"
#include "Engine/Core/SystemManagement/SystemContainer.h"

void ScriptedSystemInterface::RegisterSystemInstance(MonoObject* object)
{
	ScriptedSystem* newSystem = new ScriptedSystem(object);
	SystemContainer* sysContainer = GlobalStaticReferences::Instance()->GetSystemContainer();
	sysContainer->RegisterSystem(newSystem);
	ScriptedSystemLoader* systemLoader = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	systemLoader->RegisterSubsystem(newSystem);
}

void ScriptedSystemInterface::RegisterMonoMethods()
{
	mono_add_internal_call("MonoSystemInterface::RegisterSystem", ScriptedSystemInterface::RegisterSystemInstance);
}
