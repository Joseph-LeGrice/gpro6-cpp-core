#include "stdafx.h"

#include "Graphics/ResourceTypes/StructuredBuffer.h"
#include "SystemManagement/Systems/GraphicsSystem.h"


void StructuredBuffer::BindResource(UINT resourceIndex)
{
    ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->VSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->HSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->DSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->GSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->PSSetShaderResources(resourceIndex, 1, m_resourceView);
}

void StructuredBuffer::Release()
{
    m_buffer.ReleasePointer();
    m_resourceView.ReleasePointer();
}
