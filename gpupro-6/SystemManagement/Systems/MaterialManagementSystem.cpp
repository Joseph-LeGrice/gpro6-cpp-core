#include "stdafx.h"
#include "SystemManagement/Systems/MaterialManagementSystem.h"


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

const int MaterialManagementSystem::RegisterInstancedMaterial(Material& m)
{
	int index = static_cast<int>(m_instancedMaterials.size());
	m_instancedMaterials.push_back(&m);
	return index;
}

Material* MaterialManagementSystem::GetMaterial(int index)
{
	if (index >= 0 && index < m_instancedMaterials.size())
	{
		return m_instancedMaterials[index];
	}
	else
	{
		return nullptr;
	}
}

const int MaterialManagementSystem::RegisterShaderResource(ShaderResource& sr)
{
	int index = static_cast<int>(m_shaderResources.size());
	m_shaderResources.push_back(&sr);
	return index;
}

ShaderResource* MaterialManagementSystem::GetShaderResource(int index)
{
	if (index >= 0 && index < m_shaderResources.size())
	{
		return m_shaderResources[index];
	}
	else
	{
		return nullptr;
	}
}

const int MaterialManagementSystem::RegisterTextureSampler(TextureSampler& ts)
{
	int index = static_cast<int>(m_textureSamplers.size());
	m_textureSamplers.push_back(&ts);
	return index;
}

TextureSampler* MaterialManagementSystem::GetTextureSampler(int index)
{
	if (index >= 0 && index < m_textureSamplers.size())
	{
		return m_textureSamplers[index];
	}
	else
	{
		return nullptr;
	}
}

const std::vector<Mesh*>* MaterialManagementSystem::GetAllMeshes()
{
	return &m_meshes;
}

const int MaterialManagementSystem::RegisterMesh(Mesh& m)
{
	int index = static_cast<int>(m_meshes.size());
	m_meshes.push_back(&m);
	return index;

}

Mesh* MaterialManagementSystem::GetMesh(int meshIndex)
{
	if (meshIndex >= 0 && meshIndex < m_meshes.size())
	{
		return m_meshes[meshIndex];
	}
	else
	{
		return nullptr;
	}
}
