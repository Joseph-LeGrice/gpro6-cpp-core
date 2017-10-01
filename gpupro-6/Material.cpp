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

Material::Material()
{
	m_shader = nullptr;
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

bool Material::Initialize()
{
	return InitializeBuffers();
}


void Material::DeregisterMeshInfo(size_t meshIndex, size_t transformIndex)
{
	size_t lastIndex = m_renderMap[meshIndex].size() - 1;
	m_renderMap[meshIndex][transformIndex] = m_renderMap[meshIndex][lastIndex];
	m_renderMap[meshIndex].resize(lastIndex);
}


void Material::RegisterMeshInfo(size_t meshIndex, size_t transformIndex)
{
	if (!m_renderMap.count(meshIndex))
	{
		m_renderMap[meshIndex] = std::vector<size_t>();
	}
	m_renderMap[meshIndex].push_back(transformIndex);
}

void Material::SetShader(Shader* s)
{
	m_shader = s;
}

bool Material::InitializeBuffers()
{
	ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();
	
	size_t INDEX_BUFFER_SIZE = 1024;
	size_t VERTEX_BUFFER_SIZE = 1024;

	m_myIndexBuffer = IndexBuffer::Create(INDEX_BUFFER_SIZE);
	m_myVertexBuffer = VertexBuffer::Create(VERTEX_BUFFER_SIZE);

	return m_myIndexBuffer != nullptr && m_myVertexBuffer != nullptr;
}


void Material::Render(ConstantBuffer* constBuf)
{
	if (m_shader != nullptr && m_shader->SetCurrentIfValid())
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
		m_myVertexBuffer->SetData(allVerts);
		m_myIndexBuffer->SetData(allIndices);

		PODArray<VertexData>::Free(allVerts);
		PODArray<UINT16>::Free(allIndices);

		m_myVertexBuffer->SetCurrentIfValid();
		m_myIndexBuffer->SetCurrentIfValid();
		
		ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
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
