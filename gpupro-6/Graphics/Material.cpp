#include "stdafx.h"

#include <vector>
#include <algorithm>

#include "Components/Entity.h"
#include "Components/Transform.h"
#include "DataStructures/Mesh.h"
#include "DataStructures/SceneGraph.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/TextureSampler.h"
#include "Graphics/ResourceTypes/ShaderResource.h"
#include "Systems/MaterialManagementSystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/SceneManagementSystem.h"
#include "Systems/ConstantBufferManagementSystem.h"
#include "Systems/MaterialManagementSystem.h"
#include "Utilities/Logging.h"

Material::Material()
{
	m_shader = nullptr;
}

Material::~Material()
{
}

size_t Material::Create()
{
	Material* newMaterial = new Material();
	return MaterialManagementSystem::Instance()->RegisterInstancedMaterial(*newMaterial);
}

void Material::SetShader(Shader* s, size_t numberOfResources, size_t numberOfSamplers)
{
	m_shader = s;
	
	m_shaderResourceIndexes.resize(numberOfResources);
	for (int i = 0; i < numberOfResources; ++i)
	{
		m_shaderResourceIndexes[i] = -1;
	}
	
	m_textureSamplerIndexes.resize(numberOfSamplers);
	for (int i = 0; i < numberOfSamplers; ++i)
	{
		m_textureSamplerIndexes[i] = -1;
	}
}

void Material::AddShaderResource(size_t shaderResourceIndex, size_t shaderResourceSlotIndex)
{
	m_shaderResourceIndexes[shaderResourceSlotIndex] = shaderResourceIndex;
}

void Material::RemoveShaderResource(size_t shaderResourceSlotIndex)
{
	m_shaderResourceIndexes[shaderResourceSlotIndex] = -1;
}

void Material::AddTextureSampler(size_t textureSamplerIndex, size_t textureSamplerSlotIndex)
{
	m_textureSamplerIndexes[textureSamplerSlotIndex] = textureSamplerIndex;
}

void Material::RemoveTextureSampler(size_t textureSamplerSlotIndex)
{
	m_textureSamplerIndexes[textureSamplerSlotIndex] = -1;
}

void Material::Bind()
{
	if (m_shader != nullptr && m_shader->SetCurrentIfValid())
	{
		std::vector<ShaderResource*> allResources = *MaterialManagementSystem::Instance()->GetAllShaderResources();
		for (size_t shaderResourceSlot = 0; shaderResourceSlot < m_shaderResourceIndexes.size(); ++shaderResourceSlot)
		{
			size_t shaderResourceIndex = m_shaderResourceIndexes[shaderResourceSlot];
			allResources[shaderResourceIndex]->BindResource(shaderResourceSlot, m_shaderResourceIndexes.size());
		}

		std::vector<TextureSampler*> allTexturesSamplers = *MaterialManagementSystem::Instance()->GetAllTextureSamplers();
		for (size_t textureSamplerSlot = 0; textureSamplerSlot < m_textureSamplerIndexes.size(); ++textureSamplerSlot)
		{
			size_t textureSamplerIndex = m_textureSamplerIndexes[textureSamplerSlot];
			allTexturesSamplers[textureSamplerIndex]->BindTextureSampler(textureSamplerSlot, m_textureSamplerIndexes.size());
		}
	}
}
