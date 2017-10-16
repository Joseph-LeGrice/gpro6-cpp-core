#include "stdafx.h"

#include <vector>
#include <algorithm>

#include "Components/Entity.h"
#include "Components/Transform.h"
#include "DataStructures/Mesh.h"
#include "DataStructures/SceneGraph.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/TextureSampler.h"
#include "Graphics/ShaderResource.h"
#include "Systems/MaterialManagementSystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/SceneManagementSystem.h"
#include "Systems/ConstantBufferManagementSystem.h"
#include "Systems/MaterialManagementSystem.h"
#include "Utilities/Logging.h"

Material::Material()
{
	m_shader = nullptr;
	m_isDirty = false;
	m_myIndexBuffer = nullptr;
	m_myVertexBuffer = nullptr;
}

Material::~Material()
{
	SAFE_DELETE(m_myVertexBuffer);
	SAFE_DELETE(m_myIndexBuffer);
}

Material* Material::Create()
{
	Material* newMaterial = new Material();
	if (newMaterial->Initialize())
	{
		MaterialManagementSystem::Instance()->RegisterInstancedMaterial(*newMaterial);
		return newMaterial;
	}
	else
	{
		SAFE_DELETE(newMaterial);
		return nullptr;
	}
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


void Material::RegisterMeshInfo(size_t meshIndex, size_t transformIndex)
{
	if (!m_renderMap.count(meshIndex))
	{
		m_renderMap[meshIndex] = std::vector<size_t>();
	}
	m_renderMap[meshIndex].push_back(transformIndex);
	m_isDirty = true;
}


void Material::DeregisterMeshInfo(size_t meshIndex, size_t transformIndex)
{
	size_t lastIndex = m_renderMap[meshIndex].size() - 1;
	m_renderMap[meshIndex][transformIndex] = m_renderMap[meshIndex][lastIndex];
	m_renderMap[meshIndex].resize(lastIndex);
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


bool Material::Initialize()
{
	size_t INDEX_BUFFER_SIZE = (size_t)pow(1024, 2);
	size_t VERTEX_BUFFER_SIZE = (size_t)pow(1024, 2);

	m_myIndexBuffer = IndexBuffer::Create(INDEX_BUFFER_SIZE);
	m_myVertexBuffer = VertexBuffer::Create(VERTEX_BUFFER_SIZE);

	return m_myIndexBuffer != nullptr && m_myVertexBuffer != nullptr;
}


void Material::UpdateIfDirty()
{
	if (m_isDirty)
	{
		SceneGraph* sg = SceneManagementSystem::Instance()->GetSceneGraph();
		const std::vector<Mesh*>& allMeshes = *MaterialManagementSystem::Instance()->GetAllMeshes();

		std::vector<VertexData> allVerts;
		std::vector<UINT16> allIndices;

		for (auto it = m_renderMap.begin(); it != m_renderMap.end(); ++it)
		{
			Mesh& m = *allMeshes[it->first];

			const std::vector<VertexData>& vertexData = m.GetVertexData();
			allVerts.insert(allVerts.end(), vertexData.begin(), vertexData.end());
			
			const std::vector<UINT16>& indexData = m.GetIndices();
			allIndices.insert(allIndices.end(), indexData.begin(), indexData.end());
		}

		if (m_myVertexBuffer->TrySetData(allVerts) &&
			m_myIndexBuffer->TrySetData(allIndices))
		{
			m_isDirty = false;
		}
	}
}

void Material::Render(Matrix4x4& proj, Matrix4x4& view)
{
	if (m_shader != nullptr && m_shader->SetCurrentIfValid())
	{
		m_myVertexBuffer->SetCurrentIfValid();
		m_myIndexBuffer->SetCurrentIfValid();
		
		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
		
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

		PER_OBJECT_BUFFER pob;
		SceneGraph* sg = SceneManagementSystem::Instance()->GetSceneGraph();
		const std::vector<Mesh*>& allMeshes = *MaterialManagementSystem::Instance()->GetAllMeshes();
		Transform* const allTransforms = sg->m_transforms.GetArrayPointer();

		PerObjectBuffer& pub = ConstantBufferManagementSystem::Instance()->GetPerObjectBuffer();
		UINT16 currentIndex = 0;
		for (auto it = m_renderMap.begin(); it != m_renderMap.end(); ++it)
		{
			Mesh& m = *allMeshes[it->first];
			for (auto transformIt = it->second.begin(); transformIt != it->second.end(); ++transformIt)
			{
				Transform& t = allTransforms[*transformIt];
				Matrix4x4 model = TransformGetMatrix(t);

				pob.ModelViewProjection = proj * view * model;
				pob.ModelView = view * model;
				pub.UpdateBuffer(pob);

				UINT16 numberOfVerts = (UINT16)m.GetIndices().size();
				deviceContext->IASetPrimitiveTopology(m.m_topology);
				deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
				currentIndex += numberOfVerts;
			}
		}
	}
}
