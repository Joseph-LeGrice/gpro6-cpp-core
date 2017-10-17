#include "stdafx.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "DataStructures/VertexData.h"
#include "Systems/GraphicsSystem.h"

VertexBuffer::VertexBuffer()
{
	m_vertexBuffer = nullptr;
}

VertexBuffer::~VertexBuffer()
{
	SAFE_RELEASE(m_vertexBuffer);
}

bool VertexBuffer::SetCurrentIfValid()
{
	UINT offset = 0;
	UINT stride = sizeof(VertexData);
	
	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	return true;
}

VertexBuffer* VertexBuffer::Create(size_t bufferSize)
{
	VertexBuffer* vb = new VertexBuffer();

	ID3D11Device* device = GraphicsSystem::Instance()->GetGraphicsDevice();

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = (UINT)(sizeof(VertexData) * bufferSize);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, NULL, &vb->m_vertexBuffer);
	if (SUCCEEDED(vertexBufferCreation))
	{
		return vb;
	}
	else
	{
		SAFE_DELETE(vb);
		return nullptr;
	}
}


bool VertexBuffer::TrySetData(const std::vector<VertexData>& data)
{
	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();

	D3D11_MAPPED_SUBRESOURCE vertexData;
	HRESULT vertexBufferAcquireResult = deviceContext->Map(m_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &vertexData);
	if (SUCCEEDED(vertexBufferAcquireResult))
	{
		memcpy(vertexData.pData, &data[0], sizeof(VertexData) * data.size());
		deviceContext->Unmap(m_vertexBuffer, 0);
		return true;
	}
	return false;
}
