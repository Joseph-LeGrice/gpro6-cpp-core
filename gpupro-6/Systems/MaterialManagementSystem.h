#pragma once

#include <vector>
#include "Graphics\Material.h"
#include "Systems\GameSystem.h"

class MaterialManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(MaterialManagementSystem)

public:
	const std::vector<Material*>* GetAllMaterials();
	const size_t RegisterInstancedMaterial(Material&);

	const std::vector<ShaderResource*>* GetAllShaderResources();
	const size_t RegisterShaderResource(ShaderResource&);
	
	const std::vector<TextureSampler*>* GetAllTextureSamplers();
	const size_t RegisterTextureSampler(TextureSampler&);

private:
	std::vector<Material*> m_instancedMaterials;
	std::vector<ShaderResource*> m_shaderResources;
	std::vector<TextureSampler*> m_textureSamplers;
};

