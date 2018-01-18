#include "stdafx.h"

#include "Engine/Core/Utilities/Logging.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Utilities/PerlinNoise.h"
#include "FreeImage.h"

Texture2D::Texture2D(UINT resourceId) : IResource(resourceId)
{
    m_bitmap = nullptr;
}

Texture2D::~Texture2D()
{
}

UINT Texture2D::GetResourceViewID()
{
    return m_myShaderResourceViewId;
}

void Texture2D::InitializeWithBitmap(const wchar_t* filepath)
{
    Release();

    FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeU(filepath);
    if (fif != FIF_UNKNOWN)
    {
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

    ID3D11Device* device = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDevice();
    HRESULT createTextureResult = device->CreateTexture2D(&desc, &data, m_pTexture);
    if (SUCCEEDED(createTextureResult))
    {
        ShaderResource* myShaderResourceView = GetResourceManager().Instantiate<ShaderResource>();
        m_myShaderResourceViewId = myShaderResourceView->GetResourceID();

        bool createdView = myShaderResourceView->CreateViewWithResource(m_pTexture, NULL);
        if (!createdView)
        {
            GetResourceManager().Deallocate<ShaderResource>(m_myShaderResourceViewId);
            LogError("Could not create resource view");
        }
    }
    else
    {
        LogError("Could not create texture");
    }
}

void Texture2D::Release()
{
    if (m_bitmap != nullptr)
    {
        FreeImage_Unload(m_bitmap);
    }
    m_pTexture.ReleasePointer();
}
