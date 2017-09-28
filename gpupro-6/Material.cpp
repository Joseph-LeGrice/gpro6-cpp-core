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

Material::Material()
{
	m_shader = nullptr;
	m_indexBuffer = nullptr;
	m_vertexBuffer = nullptr;
}

Material::~Material()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);
	SAFE_DELETE(m_shader);
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
	
	int INDEX_BUFFER_SIZE = 1024;
	int VERTEX_BUFER_SIZE = 1024;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(UINT16) * INDEX_BUFFER_SIZE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	HRESULT indexBufferCreationResult = device->CreateBuffer(&indexBufferDesc, NULL, &m_indexBuffer);
	
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * VERTEX_BUFER_SIZE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, NULL, &m_vertexBuffer);

	return SUCCEEDED(indexBufferCreationResult) && SUCCEEDED(vertexBufferCreation);
}


void Material::Render(ConstantBuffer* constBuf)
{
	m_shader->SetCurrent();

	UINT offset = 0;
	UINT stride = sizeof(VertexData);

	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

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

	D3D11_MAPPED_SUBRESOURCE vertexData;
	HRESULT vertexBufferAcquireResult = deviceContext->Map(m_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &vertexData);
	if (SUCCEEDED(vertexBufferAcquireResult))
	{
		memcpy(vertexData.pData, PODArray<VertexData>::GetArrayPointer(allVerts), sizeof(VertexData) * PODArray<VertexData>::Size(allVerts));
		deviceContext->Unmap(m_vertexBuffer, 0);
	}

	D3D11_MAPPED_SUBRESOURCE indexBufferData;
	HRESULT indexBufferAcquireResult = deviceContext->Map(m_indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &indexBufferData);
	if (SUCCEEDED(indexBufferAcquireResult))
	{
		memcpy(indexBufferData.pData, PODArray<UINT16>::GetArrayPointer(allIndices), sizeof(UINT16) * PODArray<UINT16>::Size(allIndices));
		deviceContext->Unmap(m_indexBuffer, 0);
	}

	PODArray<VertexData>::Free(allVerts);
	PODArray<UINT16>::Free(allIndices);

	Transform* allTransforms = sg->m_transforms.GetArrayPointer();
	
	int currentIndex = 0;
	for (auto it = m_renderMap.begin(); it != m_renderMap.end(); ++it)
	{
		Mesh& m = allMeshes[it->first];
		for (auto transformIt = it->second.begin(); transformIt != it->second.end(); ++transformIt)
		{
			Transform& t = allTransforms[*transformIt];
			constBuf->SetWorldMatrix(Transform::GetTransformationMatrix(t));
			constBuf->UpdateBuffers();

			size_t numberOfVerts = PODArray<UINT16>::Size(m.m_indices);
			deviceContext->IASetPrimitiveTopology(m.m_topology);
			deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
			currentIndex += numberOfVerts;
		}
	}
}
