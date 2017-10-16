#include "stdafx.h"
#include "MaterialManagementSystem.h"


MaterialManagementSystem::MaterialManagementSystem()
{
	m_instancedMaterials = std::vector<Material*>();
}


MaterialManagementSystem::~MaterialManagementSystem()
{
	SAFE_DELETE_VECTOR_STACK(m_instancedMaterials);
	SAFE_DELETE_VECTOR_STACK(m_textureSamplers);
	SAFE_DELETE_VECTOR_STACK(m_shaderResources);
}

const std::vector<Material*>* MaterialManagementSystem::GetAllMaterials()
{
	return &m_instancedMaterials;
}

const size_t MaterialManagementSystem::RegisterInstancedMaterial(Material& m)
{
	size_t index = m_instancedMaterials.size();
	m_instancedMaterials.push_back(&m);
	return index;
}

const std::vector<ShaderResource*>* MaterialManagementSystem::GetAllShaderResources()
{
	return &m_shaderResources;
}

const size_t MaterialManagementSystem::RegisterShaderResource(ShaderResource& sr)
{
	size_t index = m_shaderResources.size();
	m_shaderResources.push_back(&sr);
	return index;
}

const std::vector<TextureSampler*>* MaterialManagementSystem::GetAllTextureSamplers()
{
	return &m_textureSamplers;
}

const size_t MaterialManagementSystem::RegisterTextureSampler(TextureSampler& ts)
{
	size_t index = m_textureSamplers.size();
	m_textureSamplers.push_back(&ts);
	return index;
}
