#include "stdafx.h"
#include "ShaderResource.h"

#include "D3D11.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/GlobalStaticReferences.h"

void ShaderResource::BindResource(UINT resourceIndex)
{
    ID3D11DeviceContext* deviceContext = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDeviceContext();
    deviceContext->VSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->HSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->DSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->GSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->PSSetShaderResources(resourceIndex, 1, m_resourceView);
}

bool ShaderResource::CreateViewWithResource(ID3D11Resource& resource, D3D11_SHADER_RESOURCE_VIEW_DESC* desc)
{
    ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
    HRESULT hr = device->CreateShaderResourceView(&resource, desc, m_resourceView);
    return SUCCEEDED(hr);
}

void ShaderResource::Release()
{
    m_resourceView.ReleasePointer();
}
