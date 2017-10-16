#include "stdafx.h"
#include "Systems/MaterialManagementSystem.h"


MaterialManagementSystem::MaterialManagementSystem()
{
	m_instancedMaterials = std::vector<Material*>();
}


MaterialManagementSystem::~MaterialManagementSystem()
{
	SAFE_DELETE_VECTOR_STACK(m_instancedMaterials);
	SAFE_DELETE_VECTOR_STACK(m_textureSamplers);
	SAFE_DELETE_VECTOR_STACK(m_shaderResources);
	SAFE_DELETE_VECTOR_STACK(m_meshes);
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

const std::vector<Mesh*>* MaterialManagementSystem::GetAllMeshes()
{
	return &m_meshes;
}

const size_t MaterialManagementSystem::RegisterMesh(Mesh& m)
{
	size_t index = m_meshes.size();
	m_meshes.push_back(&m);
	return index;

}

Mesh& MaterialManagementSystem::GetMesh(size_t meshIndex)
{
	return *m_meshes[meshIndex];
}
