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

void ConstantBuffer::BindBuffer()
{
    UINT bufferSlot = GetBufferSlot();
    BindFlags bindFlags = GetBindFlags();

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
