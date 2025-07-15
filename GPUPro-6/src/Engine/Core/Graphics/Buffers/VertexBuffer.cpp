#include "stdafx.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/VertexData.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "D3D11.h"

VertexBuffer::VertexBuffer(GraphicsDevice& gfxDevice) : m_gfxDevice(gfxDevice)
{
	ID3D11Device* device = m_gfxDevice.GetGraphicsDevice();

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = (UINT)(sizeof(VertexData) * VERTEX_BUFFER_SIZE);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT vertexBufferCreation = device->CreateBuffer(&vertexBufferDesc, NULL, m_vertexBuffer);
	custom_assert::is_true(SUCCEEDED(vertexBufferCreation), "Could not create vertex buffer!");
}

VertexBuffer::~VertexBuffer()
{
}

bool VertexBuffer::SetCurrentIfValid()
{
	UINT offset = 0;
	UINT stride = sizeof(VertexData);
	
	ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();
	deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer, &stride, &offset);

	return true;
}


bool VertexBuffer::TrySetData(const std::vector<VertexData>& data)
{
	ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();

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
