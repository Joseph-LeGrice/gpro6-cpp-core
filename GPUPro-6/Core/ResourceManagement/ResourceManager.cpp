#include "stdafx.h"
#include "Core/ResourceManagement/ResourceManager.h"

ResourceManager* s_instance = new ResourceManager();

ResourceManager& GetResourceManager()
{
    return *s_instance;
}

void DestroyResourceManager()
{
    s_instance->DeallocateAll<Shader>();
    s_instance->DeallocateAll<Texture2D>();
    s_instance->DeallocateAll<Texture2DArray>();
    s_instance->DeallocateAll<StructuredBuffer>();
    s_instance->DeallocateAll<TextureSampler>();
    delete s_instance;
}
