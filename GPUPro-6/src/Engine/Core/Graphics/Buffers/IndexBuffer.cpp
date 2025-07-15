#include "stdafx.h"
#include "IndexBuffer.h"

#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "D3D11.h"


IndexBuffer::IndexBuffer(GraphicsDevice& gfxDevice) : m_gfxDevice(gfxDevice)
{
	ID3D11Device* device = m_gfxDevice.GetGraphicsDevice();

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = (UINT)(sizeof(UINT16) * INDEX_BUFFER_SIZE);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	HRESULT indexBufferCreationResult = device->CreateBuffer(&indexBufferDesc, NULL, m_indexBuffer);
	custom_assert::is_true(SUCCEEDED(indexBufferCreationResult), "Could not create index buffer!");
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::SetCurrentIfValid()
{
	ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	return true;
}

bool IndexBuffer::TrySetData(const std::vector<UINT16>& data)
{
	ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();
	
	D3D11_MAPPED_SUBRESOURCE indexBufferData;
	HRESULT indexBufferAcquireResult = deviceContext->Map(m_indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &indexBufferData);
	if (SUCCEEDED(indexBufferAcquireResult))
	{
		memcpy(indexBufferData.pData, &data[0], sizeof(UINT16) * data.size());
		deviceContext->Unmap(m_indexBuffer, 0);
		return true;
	}
	return false;
}
