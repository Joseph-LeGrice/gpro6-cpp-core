#pragma once

#include "Engine/Core/Graphics/ShaderResource.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/ResourceTypes/Material.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"


#include "Engine/Core/ResourceManagement/ResourceManagerDefinition.hpp"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"

typedef ResourceManagerDefinition<
    Shader,
    Mesh,
    TextureSampler,
    Texture2D,
    Texture2DArray,
    StructuredBuffer,
    Material,
    ShaderResource
> ResourceManager;

ResourceManager& GetResourceManager();
void DestroyResourceManager();
