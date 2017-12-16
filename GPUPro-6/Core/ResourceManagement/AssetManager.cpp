#include "stdafx.h"
#include "Core/ResourceManagement/AssetManager.h"

AssetManager* s_instance = new AssetManager();

AssetManager& GetAssetManager()
{
    return *s_instance;
}

void DestroyAssetManager()
{
    s_instance->DeallocateAll<Shader>();
    s_instance->DeallocateAll<Texture2D>();
    s_instance->DeallocateAll<Texture2DArray>();
    s_instance->DeallocateAll<StructuredBuffer>();
    s_instance->DeallocateAll<TextureSampler>();
    delete s_instance;
}
