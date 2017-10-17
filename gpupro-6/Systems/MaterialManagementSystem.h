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
	const size_t RegisterInstancedMaterial(Material& m);
	Material& GetMaterial(size_t index);

	const std::vector<ShaderResource*>* GetAllShaderResources();
	const size_t RegisterShaderResource(ShaderResource& sr);
	
	const std::vector<TextureSampler*>* GetAllTextureSamplers();
	const size_t RegisterTextureSampler(TextureSampler& ts);

	const std::vector<Mesh*>* GetAllMeshes();
	const size_t RegisterMesh(Mesh& m);
	Mesh& GetMesh(size_t meshIndex);

private:
	std::vector<Material*> m_instancedMaterials;
	std::vector<ShaderResource*> m_shaderResources;
	std::vector<TextureSampler*> m_textureSamplers;
	std::vector<Mesh*> m_meshes;
};

