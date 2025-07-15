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
#include "Engine/Core/ResourceTypes/Material.h"


#include "Engine/Core/Components/Camera.h"
#include "Engine/Core/Components/Light.h"
#include "Engine/Core/Components/MeshRenderer.h"
#include "Engine/Core/Components/Transform.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"


void RegisterAllTypes()
{
	RegisterManagedType<Mesh>("Mesh");
	RegisterManagedType<Shader>("Shader");
	RegisterManagedType<Texture2D>("Texture2D");
	RegisterManagedType<ShaderResource>("ShaderResource");
	RegisterManagedType<Texture2DArray>("Texture2DArray");
	RegisterManagedType<TextureSampler>("TextureSampler");
	RegisterManagedType<Material>("Material");
	RegisterManagedType<StructuredBuffer>("StructuredBuffer");
	RegisterManagedType<Material>("Material");
	RegisterType<ManagedObject>();

	RegisterManagedType<Transform>("Transform");
	RegisterManagedType<Camera>("Camera");
	RegisterManagedType<MeshRenderer>("MeshRenderer");
	RegisterManagedType<Entity>("Entity");
	RegisterManagedType<Light>("Light");
}