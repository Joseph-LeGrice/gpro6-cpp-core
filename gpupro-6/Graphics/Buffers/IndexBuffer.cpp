#include "stdafx.h"
#include "IndexBuffer.h"
#include "SystemManagement/SystemManager.h"


IndexBuffer::IndexBuffer()
{
	m_indexBuffer = nullptr;
}


IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(m_indexBuffer);
}

IndexBuffer* IndexBuffer::Create(size_t bufferSize)
{
	IndexBuffer* ib = new IndexBuffer();
	ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = (UINT)(sizeof(UINT16) * bufferSize);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	HRESULT indexBufferCreationResult = device->CreateBuffer(&indexBufferDesc, NULL, &ib->m_indexBuffer);
	if (SUCCEEDED(indexBufferCreationResult))
	{
		return ib;
	}
	else
	{
		SAFE_DELETE(ib);
		return nullptr;
	}
}

bool IndexBuffer::SetCurrentIfValid()
{
	ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	return true;
}

bool IndexBuffer::TrySetData(const std::vector<UINT16>& data)
{
	ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
	
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
