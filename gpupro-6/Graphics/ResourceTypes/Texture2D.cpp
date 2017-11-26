#include "stdafx.h"

#include "Utilities/Logging.h"
#include "Graphics/ResourceTypes/Texture2D.h"
#include "SystemManagement/SystemManager.h"
#include "AssetManagement/AssetManager.h"
#include "Utilities/PerlinNoise.h"
#include "FreeImage.h"

Texture2D::Texture2D(UINT resourceId) : IResource(resourceId)
{
    m_bitmap = nullptr;
	m_pTexture = nullptr;
	m_resourceView = nullptr;
}

Texture2D::~Texture2D()
{
    ReleaseResources();
}

void Texture2D::InitializeWithBitmap(const wchar_t* filepath)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeU(filepath);
    if (fif != FIF_UNKNOWN)
    {
        ReleaseResources();

        FIBITMAP* bmp = FreeImage_LoadU(fif, filepath);
        m_bitmap = FreeImage_ConvertTo32Bits(bmp);
        FreeImage_Unload(bmp);

        CreateResources();
    }
    else
    {
        LogError("Could not load bitmap FREE_IMAGE_FORMAT == FIF_UNKNOWN");
    }
}

void Texture2D::CreateResources()
{
    UINT pitch = FreeImage_GetPitch(m_bitmap);
    UINT width = FreeImage_GetWidth(m_bitmap);
    UINT height = FreeImage_GetHeight(m_bitmap);

    DXGI_FORMAT pixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    BYTE* pbBuffer = FreeImage_GetBits(m_bitmap);

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = pixelFormat;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = pbBuffer;
    data.SysMemPitch = pitch;
    data.SysMemSlicePitch = pitch * height;

    ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
    HRESULT createTextureResult = device->CreateTexture2D(&desc, &data, &m_pTexture);
    if (SUCCEEDED(createTextureResult))
    {
        HRESULT createResourceViewResult = device->CreateShaderResourceView(m_pTexture, NULL, &m_resourceView);
        if (!SUCCEEDED(createResourceViewResult))
        {
            LogError("Could not create resource view");
        }
    }
    else
    {
        LogError("Could not create texture");
    }
}

void Texture2D::BindResource(UINT resourceIndex)
{
    ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->VSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->HSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->DSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->GSSetShaderResources(resourceIndex, 1, &m_resourceView);
    deviceContext->PSSetShaderResources(resourceIndex, 1, &m_resourceView);
}

void Texture2D::ReleaseResources()
{
    if (m_bitmap != nullptr)
    {
        FreeImage_Unload(m_bitmap);
    }
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_resourceView);
}
