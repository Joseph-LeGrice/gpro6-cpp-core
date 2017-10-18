#pragma once

#include <vector>
#include "Graphics/Material.h"
#include "Graphics/ResourceTypes/ShaderResource.h"
#include "Graphics/TextureSampler.h"
#include "DataStructures/Mesh.h"

#include "Systems/GameSystem.h"


class MaterialManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(MaterialManagementSystem)

public:
	const std::vector<Material*>* GetAllMaterials();
	const int RegisterInstancedMaterial(Material& m);
	Material* GetMaterial(int index);

	const int RegisterShaderResource(ShaderResource& sr);
	ShaderResource* GetShaderResource(int index);

	const int RegisterTextureSampler(TextureSampler& ts);
	TextureSampler* GetTextureSampler(int index);

	const std::vector<Mesh*>* GetAllMeshes();
	const int RegisterMesh(Mesh& m);
	Mesh* GetMesh(int meshIndex);

private:
	std::vector<Material*> m_instancedMaterials;
	std::vector<ShaderResource*> m_shaderResources;
	std::vector<TextureSampler*> m_textureSamplers;
	std::vector<Mesh*> m_meshes;
};

