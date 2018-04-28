#include "stdafx.h"
#include "HelperMethods.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/ResourceTypes/ShaderResource.h"
#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"
#include "Engine/Core/Scripting/ManagedObject.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/SimpleMaterial.h"
#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"

void RegisterAllTypes()
{
	RegisterManagedType<Texture2D>("Texture2D");
	RegisterType<Mesh>();
	RegisterType<Shader>();
	RegisterType<ShaderResource>();
	RegisterType<StructuredBuffer>();
	RegisterType<Texture2D>();
	RegisterType<Texture2DArray>();
	RegisterType<TextureSampler>();
	RegisterType<SimpleMaterial>();
	RegisterType<StandardMaterial>();
	RegisterType<ManagedObject>();
}