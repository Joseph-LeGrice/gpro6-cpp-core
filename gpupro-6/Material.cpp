#include "stdafx.h"
#include <algorithm>
#include "Material.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "MaterialManagementSystem.h"
#include "GraphicsSystem.h"
#include "Shader.h"
#include "SceneManagementSystem.h"
#include "SceneGraph.h"
#include "Entity.h"
#include "Transform.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Logging.h"
#include "TextureSampler.h"
#include "ShaderResource.h"

Material::Material()
{
	m_shader = nullptr;
	m_isDirty = false;
	m_myIndexBuffer = nullptr;
	m_myVertexBuffer = nullptr;
	m_shaderResources = std::vector<ShaderResource*>();
	m_textureSamplers = std::vector<TextureSampler*>();
}

Material::~Material()
{
	SAFE_DELETE(m_myVertexBuffer);
	SAFE_DELETE(m_myIndexBuffer);

	SAFE_DELETE_VECTOR_STACK(m_textureSamplers);
	SAFE_DELETE_VECTOR_STACK(m_shaderResources);
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


void Material::SetShader(Shader* s)
{
	m_shader = s;
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


void Material::AddShaderResource(ShaderResource* r)
{
	if (r != nullptr)
	{
		m_shaderResources.push_back(r);
	}
	else
	{
		LogError("ShaderResource is not valid!");
	}
}

void Material::RemoveShaderResource(ShaderResource* r)
{
	m_shaderResources.erase(std::remove(m_shaderResources.begin(), m_shaderResources.end(), r), m_shaderResources.end());
}


void Material::AddTextureSampler(TextureSampler* ts)
{
	if (ts != nullptr && ts->IsValid())
	{
		m_textureSamplers.push_back(ts);
	}
	else
	{
		LogError("TextureSampler is not valid!");
	}
}

void Material::RemoveTextureSampler(TextureSampler* ts)
{
	m_textureSamplers.erase(std::remove(m_textureSamplers.begin(), m_textureSamplers.end(), ts), m_textureSamplers.end());
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
		Mesh* allMeshes = sg->m_meshes.GetArrayPointer();

		PODArray<VertexData> allVerts = PODArray<VertexData>::New();
		PODArray<UINT16> allIndices = PODArray<UINT16>::New();

		for (auto it = m_renderMap.begin(); it != m_renderMap.end(); ++it)
		{
			Mesh& m = allMeshes[it->first];
			PODArray<VertexData>::Append(allVerts, m.m_vertexData);
			PODArray<UINT16>::Append(allIndices, m.m_indices);
		}

		if (m_myVertexBuffer->TrySetData(allVerts) &&
			m_myIndexBuffer->TrySetData(allIndices))
		{
			m_isDirty = false;
		}

		PODArray<VertexData>::Free(allVerts);
		PODArray<UINT16>::Free(allIndices);
	}
}

void Material::Render(ConstantBuffer* constBuf)
{
	if (m_shader != nullptr && m_shader->SetCurrentIfValid())
	{
		m_myVertexBuffer->SetCurrentIfValid();
		m_myIndexBuffer->SetCurrentIfValid();
		
		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
		
		if (m_shaderResources.size() > 0)
		{
			std::vector<ID3D11ShaderResourceView*> allResources;
			for each (ShaderResource* sr in m_shaderResources)
			{
				ID3D11ShaderResourceView* resource = sr->GetResourceView();
				allResources.push_back(resource);
			}
			deviceContext->VSSetShaderResources(0, (UINT)allResources.size(), &allResources[0]);
			//deviceContext->HSSetShaderResources(0, allResources.size(), &allResources[0]);
			//deviceContext->DSSetShaderResources(0, allResources.size(), &allResources[0]);
			//deviceContext->GSSetShaderResources(0, allResources.size(), &allResources[0]);
			deviceContext->PSSetShaderResources(0, (UINT)allResources.size(), &allResources[0]);
		}

		if (m_textureSamplers.size() > 0)
		{
			std::vector<ID3D11SamplerState*> allSamplers;
			for each (TextureSampler* ts in m_textureSamplers)
			{
				ID3D11SamplerState* sampler = ts->GetSampler();
				allSamplers.push_back(sampler);
			}
			deviceContext->VSSetSamplers(0, (UINT)allSamplers.size(), &allSamplers[0]);
			//deviceContext->HSSetSamplers(0, allSamplers.size(), &allSamplers[0]);
			//deviceContext->DSSetSamplers(0, allSamplers.size(), &allSamplers[0]);
			//deviceContext->GSSetSamplers(0, allSamplers.size(), &allSamplers[0]);
			deviceContext->PSSetSamplers(0, (UINT)allSamplers.size(), &allSamplers[0]);
		}

		
		SceneGraph* sg = SceneManagementSystem::Instance()->GetSceneGraph();
		Mesh* allMeshes = sg->m_meshes.GetArrayPointer();
		Transform* const allTransforms = sg->m_transforms.GetArrayPointer();

		UINT16 currentIndex = 0;
		for (auto it = m_renderMap.begin(); it != m_renderMap.end(); ++it)
		{
			Mesh& m = allMeshes[it->first];
			for (auto transformIt = it->second.begin(); transformIt != it->second.end(); ++transformIt)
			{
				Transform& t = allTransforms[*transformIt];
				constBuf->SetWorldMatrix(Transform::GetTransformationMatrix(t));
				constBuf->UpdateBuffers();

				UINT16 numberOfVerts = (UINT16)PODArray<UINT16>::Size(m.m_indices);
				deviceContext->IASetPrimitiveTopology(m.m_topology);
				deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
				currentIndex += numberOfVerts;
			}
		}
	}
}
