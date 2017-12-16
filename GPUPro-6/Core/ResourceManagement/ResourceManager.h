#pragma once

#include "Core/Graphics/ResourceTypes/Shader.h"
#include "Core/Graphics/ResourceTypes/Material.h"
#include "Core/Graphics/ResourceTypes/Texture2D.h"
#include "Core/Graphics/ResourceTypes/Texture2DArray.h"
#include "Core/Graphics/ResourceTypes/StructuredBuffer.h"


#include "Core/ResourceManagement/ResourceManagerDefinition.hpp"
#include "Core/Graphics/ResourceTypes/TextureSampler.h"
#include "Core/Graphics/ResourceTypes/Mesh.h"

typedef ResourceManagerDefinition<
    Shader,
    Mesh,
    TextureSampler,
    Texture2D,
    Texture2DArray,
    StructuredBuffer,
    Material
> ResourceManager;

ResourceManager& GetResourceManager();
void DestroyResourceManager();
