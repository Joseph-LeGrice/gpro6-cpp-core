#include "stdafx.h"
#include <algorithm>
#include "Material.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "MaterialManagementSystem.h"
#include "GraphicsSystem.h"
#include "Shader.h"

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


void Material::DeregisterMeshInfo(size_t index)
{
	size_t lastIndex = m_meshes.size() - 1;
	m_meshes[index] = m_meshes[lastIndex];
	m_meshes.resize(lastIndex);
}


Mesh* Material::GetMeshInfo(size_t index)
{
	return &m_meshes[index];
}

size_t Material::RegisterMeshInfo(Mesh& m)
{
	size_t size = m_meshes.size();
	m_meshes.resize(size + 1, m);
	return size;
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
	bool indexBufferCreated = indexBufferCreationResult == S_OK;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * VERTEX_BUFER_SIZE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, NULL, &m_vertexBuffer);
	bool vertexBufferCreated = vertexBufferCreation == S_OK;

	return indexBufferCreated && vertexBufferCreated;
}


void Material::Render(ConstantBuffer* constBuf)
{
	m_shader->SetCurrent();

	UINT offset = 0;
	UINT stride = sizeof(VertexData);

	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	std::vector<VertexData> allVerts;
	std::vector<UINT16> allIndices;
	for each (Mesh m in m_meshes)
	{
		const std::vector<VertexData> verts = m.GetVertices();
		allVerts.insert(allVerts.end(), verts.begin(), verts.end());

		const std::vector<UINT16> indices = m.GetIndices();
		allIndices.insert(allIndices.end(), indices.begin(), indices.end());
	}

	D3D11_MAPPED_SUBRESOURCE vertexData;
	HRESULT vertexBufferAcquireResult = deviceContext->Map(m_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &vertexData);
	if (SUCCEEDED(vertexBufferAcquireResult))
	{
		memcpy(vertexData.pData, &allVerts[0], sizeof(VertexData) * allVerts.size());
		deviceContext->Unmap(m_vertexBuffer, 0);
	}

	D3D11_MAPPED_SUBRESOURCE indexBufferData;
	HRESULT indexBufferAcquireResult = deviceContext->Map(m_indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &indexBufferData);
	if (SUCCEEDED(indexBufferAcquireResult))
	{
		memcpy(indexBufferData.pData, &allIndices[0], sizeof(UINT16) * allIndices.size());
		deviceContext->Unmap(m_indexBuffer, 0);
	}

	int currentIndex = 0;
	for each (Mesh m in m_meshes)
	{
		//constBuf->SetWorldMatrix(m.m_transform);
		constBuf->UpdateBuffers();

		int numberOfVerts = m.GetIndices().size();
		deviceContext->IASetPrimitiveTopology(m.GetTopology());
		deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
		currentIndex += numberOfVerts;
	}
}
