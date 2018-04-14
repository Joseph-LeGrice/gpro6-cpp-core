#include "stdafx.h"
#include "MonoSystem.h"
#include "MonoSystemLoader.h"
#include "MonoSystemInterface.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/SystemManagement/SystemContainer.h"

void MonoSystemInterface::RegisterSystemInstance(MonoObject* object)
{
	MonoSystem* newSystem = new MonoSystem(object);
	SystemContainer* sysContainer = GlobalStaticReferences::Instance()->GetSystemContainer();
	sysContainer->RegisterSystem(newSystem);
	MonoSystemLoader* systemLoader = GlobalStaticReferences::Instance()->GetMonoSystemLoader();
	systemLoader->RegisterSubsystem(newSystem);
}