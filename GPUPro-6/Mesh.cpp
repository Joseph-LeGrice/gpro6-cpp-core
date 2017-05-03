#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
	m_sampleState = nullptr;
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
}

Mesh::~Mesh()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);
	SAFE_RELEASE(m_sampleState);
}

void Mesh::Render(ID3D11DeviceContext* deviceContext)
{
	UINT offset = 0;
	UINT stride = sizeof(Vertex);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(m_topology);
	deviceContext->DrawIndexed(m_numberOfIndices, 0, 0);
}

void Mesh::SetTopology(D3D_PRIMITIVE_TOPOLOGY t)
{
	m_topology = t;
}

bool Mesh::SetVertices(ID3D11Device* device, std::vector<Vertex> &verts)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * verts.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = verts.data();
	initialVertexData.SysMemPitch = 0;
	initialVertexData.SysMemSlicePitch = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, &initialVertexData, &m_vertexBuffer);
	return vertexBufferCreation == S_OK;
}

bool Mesh::SetIndices(ID3D11Device* device, std::vector<UINT16> &indices)
{
	m_numberOfIndices = indices.size();

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT16) * indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices.data();
	initialIndexData.SysMemPitch = 0;
	initialIndexData.SysMemSlicePitch = 0;

	HRESULT indexBufferCreationResult = device->CreateBuffer(&indexBufferDesc, &initialIndexData, &m_indexBuffer);
	return indexBufferCreationResult == S_OK;
}
