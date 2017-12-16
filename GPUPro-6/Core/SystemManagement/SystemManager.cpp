#include "stdafx.h"
#include "SystemManager.h"

SystemManager* g_systemManager;

void InitSystem(ISystem* s)
{
    s->Initialize();
}

void DeinitSystem(ISystem* s)
{
    s->Deinitalize();
}

void InitSystemManager()
{
    g_systemManager = new SystemManager();
    g_systemManager->ForEachSystem(InitSystem);
}

SystemManager& GetSystemManager()
{
    return *g_systemManager;
}

void DestroySystemManager()
{
    g_systemManager->ForEachSystem(DeinitSystem);
    delete g_systemManager;
}