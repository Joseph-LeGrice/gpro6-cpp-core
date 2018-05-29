#include "stdafx.h"
#include "ConstantBuffer.h"

ConstantBuffer::~ConstantBuffer()
{
    ReleaseBuffer();
}

void ConstantBuffer::ReleaseBuffer()
{
    m_buffer.ReleasePointer();
}


void ConstantBuffer::InitBuffer(UINT length)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = length;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Device* device = m_gfxDevice.GetGraphicsDevice();
	if (!SUCCEEDED(device->CreateBuffer(&desc, NULL, m_buffer)))
	{
		LogError("[ConstantBuffer] Could not Create Buffer!");
	}
}

void ConstantBuffer::UpdateBuffer(void* data, size_t length)
{
	custom_assert::is_true(length % 16 == 0, "Constant Buffer size must be divisible by 16");
	custom_assert::is_true(length <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT, "Constant Buffer size must be less than or equal to D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT");

	D3D11_MAPPED_SUBRESOURCE mappedData;
	ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();
	HRESULT bufferMapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
	if (SUCCEEDED(bufferMapResult))
	{
		memcpy(mappedData.pData, data, length);
		deviceContext->Unmap(m_buffer, 0);
	}
}

void ConstantBuffer::BindBuffer(UINT bufferSlot, BindFlags bindFlags)
{
    ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();
    if ((bindFlags & BIND_VERTEX) == BIND_VERTEX)
    {
        deviceContext->VSSetConstantBuffers(bufferSlot, 1, m_buffer);
    }
    if ((bindFlags & BIND_HULL) == BIND_HULL)
    {
        deviceContext->HSSetConstantBuffers(bufferSlot, 1, m_buffer);
    }
    if ((bindFlags & BIND_DOMAIN) == BIND_DOMAIN)
    {
        deviceContext->DSSetConstantBuffers(bufferSlot, 1, m_buffer);
    }
    if ((bindFlags & BIND_GEOM) == BIND_GEOM)
    {
        deviceContext->GSSetConstantBuffers(bufferSlot, 1, m_buffer);
    }
    if ((bindFlags & BIND_PIXEL) == BIND_PIXEL)
    {
        deviceContext->PSSetConstantBuffers(bufferSlot, 1, m_buffer);
    }
}
