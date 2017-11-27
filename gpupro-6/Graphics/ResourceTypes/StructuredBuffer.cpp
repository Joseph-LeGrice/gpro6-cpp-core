#include "stdafx.h"

#include "Graphics/ResourceTypes/StructuredBuffer.h"
#include "SystemManagement/Systems/GraphicsSystem.h"

StructuredBuffer::StructuredBuffer(UINT resourceId) : IResource(resourceId)
{
    m_buffer = nullptr;
    m_resourceView = nullptr;
}

StructuredBuffer::~StructuredBuffer()
{
}

void StructuredBuffer::BindResource(UINT resourceIndex)
{
    ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->VSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->HSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->DSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->GSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->PSSetShaderResources(resourceIndex, 1, &m_resourceView);
}

void StructuredBuffer::Release()
{
    SAFE_RELEASE(m_buffer);
    SAFE_RELEASE(m_resourceView);
}
