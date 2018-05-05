#include "stdafx.h"
#include "HelperMethods.h"
#include "Engine/Core/ResourceTypes/Mesh.h"
#include "Engine/Core/ResourceTypes/Shader.h"
#include "Engine/Core/ResourceTypes/ShaderResource.h"
#include "Engine/Core/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"
#include "Engine/Core/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/ResourceTypes/TextureSampler.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/ResourceTypes/Material/SimpleMaterial.h"
#include "Engine/Core/ResourceTypes/Material/StandardMaterial.hpp"

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