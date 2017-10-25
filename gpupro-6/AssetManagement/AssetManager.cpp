#include "stdafx.h"
#include "AssetManagement/AssetManager.h"

AssetManager* AssetManager::s_instance = nullptr;

AssetManager::AssetManager()
{
	m_instancedMaterials = std::vector<Material*>();
}


AssetManager::~AssetManager()
{
	SAFE_DELETE_VECTOR_STACK(m_instancedMaterials);
	SAFE_DELETE_VECTOR_STACK(m_textureSamplers);
	SAFE_DELETE_VECTOR_STACK(m_shaderResources);
	SAFE_DELETE_VECTOR_STACK(m_meshes);
    SAFE_DELETE_VECTOR_STACK(m_shaders);
}

// Materials
const std::vector<Material*>* AssetManager::GetAllMaterials()
{
	return &m_instancedMaterials;
}

const int AssetManager::RegisterInstancedMaterial(Material& m)
{
	int index = static_cast<int>(m_instancedMaterials.size());
	m_instancedMaterials.push_back(&m);
	return index;
}

Material* AssetManager::GetMaterial(int index)
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

// Shader Resources
const int AssetManager::RegisterShaderResource(ShaderResource& sr)
{
	int index = static_cast<int>(m_shaderResources.size());
	m_shaderResources.push_back(&sr);
	return index;
}

ShaderResource* AssetManager::GetShaderResource(int index)
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

// Texture Samplers
const int AssetManager::RegisterTextureSampler(TextureSampler& ts)
{
	int index = static_cast<int>(m_textureSamplers.size());
	m_textureSamplers.push_back(&ts);
	return index;
}

TextureSampler* AssetManager::GetTextureSampler(int index)
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

// Meshes
const std::vector<Mesh*>* AssetManager::GetAllMeshes()
{
	return &m_meshes;
}

const int AssetManager::RegisterMesh(Mesh& m)
{
	int index = static_cast<int>(m_meshes.size());
	m_meshes.push_back(&m);
	return index;

}

Mesh* AssetManager::GetMesh(int meshIndex)
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

// Shaders
void AssetManager::RegisterShader(Shader* s)
{
    m_shaders.push_back(s);
}