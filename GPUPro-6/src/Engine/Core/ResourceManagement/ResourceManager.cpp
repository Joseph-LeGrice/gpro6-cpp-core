#include "stdafx.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"

ResourceManager* s_instance = new ResourceManager();

ResourceManager& GetResourceManager()
{
    return *s_instance;
}

void DestroyResourceManager()
{
    s_instance->DeallocateAll();
    delete s_instance;
}
