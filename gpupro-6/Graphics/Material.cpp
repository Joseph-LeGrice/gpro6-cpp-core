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
#include "SystemManagement/Systems/MaterialManagementSystem.h"
#include "SystemManagement/Systems/GraphicsSystem.h"
#include "SystemManagement/Systems/SceneManagementSystem.h"
#include "SystemManagement/Systems/MaterialManagementSystem.h"
#include "Utilities/Logging.h"

Material::Material()
{
	m_shader = nullptr;
}

Material::~Material()
{
}

int Material::Create()
{
	Material* newMaterial = new Material();
	return MaterialManagementSystem::Instance()->RegisterInstancedMaterial(*newMaterial);
}

void Material::SetShader(Shader* s, size_t numberOfResources, size_t numberOfSamplers)
{
	m_shader = s;
	
	m_numberOfResources = numberOfResources;
	m_shaderResourceIndexes.resize(numberOfResources);
	for (int i = 0; i < numberOfResources; ++i)
	{
		m_shaderResourceIndexes[i] = -1;
	}
	
	m_numberOfTextureSamplers = numberOfSamplers;
	m_textureSamplerIndexes.resize(numberOfSamplers);
	for (int i = 0; i < numberOfSamplers; ++i)
	{
		m_textureSamplerIndexes[i] = -1;
	}
}

void Material::AddShaderResource(int shaderResourceIndex, size_t shaderResourceSlotIndex)
{
	if (shaderResourceSlotIndex < m_numberOfResources)
	{
		m_shaderResourceIndexes[shaderResourceSlotIndex] = shaderResourceIndex;
	}
}

void Material::RemoveShaderResource(size_t shaderResourceSlotIndex)
{
	if (shaderResourceSlotIndex < m_numberOfResources)
	{
		m_shaderResourceIndexes[shaderResourceSlotIndex] = -1;
	}
}

void Material::AddTextureSampler(int textureSamplerIndex, size_t textureSamplerSlotIndex)
{
	if (textureSamplerSlotIndex < m_numberOfTextureSamplers)
	{
		m_textureSamplerIndexes[textureSamplerSlotIndex] = textureSamplerIndex;
	}
}

void Material::RemoveTextureSampler(size_t textureSamplerSlotIndex)
{
	if (textureSamplerSlotIndex < m_numberOfTextureSamplers)
	{
		m_textureSamplerIndexes[textureSamplerSlotIndex] = -1;
	}
}

bool Material::BindIfValid()
{
	if (m_shader != nullptr && m_shader->SetCurrentIfValid())
	{
		MaterialManagementSystem& mms = *MaterialManagementSystem::Instance();

		for (size_t shaderResourceSlot = 0; shaderResourceSlot < m_shaderResourceIndexes.size(); ++shaderResourceSlot)
		{
			int shaderResourceIndex = m_shaderResourceIndexes[shaderResourceSlot];
			ShaderResource* sr = mms.GetShaderResource(shaderResourceIndex);
			if (sr != nullptr)
			{
				sr->BindResource(static_cast<UINT>(shaderResourceSlot));
			}
		}

		for (size_t textureSamplerSlot = 0; textureSamplerSlot < m_textureSamplerIndexes.size(); ++textureSamplerSlot)
		{
			int textureSamplerIndex = m_textureSamplerIndexes[textureSamplerSlot];
			TextureSampler* ts = mms.GetTextureSampler(textureSamplerIndex);
			if (ts != nullptr)
			{
				ts->BindTextureSampler(static_cast<UINT>(textureSamplerSlot));
			}
		}

        return true;
	}
    return false;
}
