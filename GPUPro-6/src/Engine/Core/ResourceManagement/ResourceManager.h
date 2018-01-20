#pragma once

#include "Engine/Core/ResourceManagement/ResourceManagerDefinition.hpp"

#include "Engine/Core/Graphics/ResourceTypes/Material.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/ResourceTypes/ShaderResource.h"
#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"

typedef ResourceManagerDefinition<
    Material,
    Mesh,
    Shader,
    ShaderResource,
    StructuredBuffer,
    Texture2D,
    Texture2DArray,
    TextureSampler
> ResourceManager;

ResourceManager& GetResourceManager();
void DestroyResourceManager();
