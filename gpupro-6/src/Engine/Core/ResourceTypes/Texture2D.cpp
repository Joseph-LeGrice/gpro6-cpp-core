#include "stdafx.h"

#include "Engine/Core/Utilities/Logging.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/DataStructures/Color.h"
#include "Engine/Core/Graphics/ResourceTypes/ShaderResource.h"

#include "D3D11.h"
#include "FreeImage.h"


unsigned int Texture2D::Width()
{
    return FreeImage_GetWidth(m_bitmap);
}

unsigned int Texture2D::Height()
{
    return FreeImage_GetHeight(m_bitmap);
}

int Texture2D::GetInstanceViewID()
{
    custom_assert::is_true(m_myShaderResourceViewIndex > -1);
    return m_myShaderResourceViewIndex;
}

void Texture2D::InitializeWithBitmap(const wchar_t* filepath)
{
    Finalize();

    FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeU(filepath);
    if (fif != FIF_UNKNOWN)
    {
        FIBITMAP* bmp = FreeImage_LoadU(fif, filepath);
        m_bitmap = FreeImage_ConvertTo32Bits(bmp);
        FreeImage_Unload(bmp);

        Creates();
    }
    else
    {
        LogError("Could not load bitmap FREE_IMAGE_FORMAT == FIF_UNKNOWN");
    }
}

void Texture2D::InitializeWithDimensions(UINT width, UINT height)
{
    m_bitmap = FreeImage_Allocate(width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
}

void Texture2D::SetPixels(Color cArray[], size_t arraySize)
{
    UINT width = FreeImage_GetWidth(m_bitmap);
    UINT height = FreeImage_GetHeight(m_bitmap);

    custom_assert::equal(static_cast<unsigned int>(arraySize), width * height);

    unsigned int bpp = FreeImage_GetLine(m_bitmap) / FreeImage_GetWidth(m_bitmap);

    unsigned int h = FreeImage_GetHeight(m_bitmap);
    unsigned int w = FreeImage_GetWidth(m_bitmap);
    for (unsigned int y = 0; y < h; y++)
    {
        BYTE* scanline = FreeImage_GetScanLine(m_bitmap, y);
        for (unsigned int x = 0; x < w; x++)
        {
            Color c = cArray[x + y * w];
            scanline[FI_RGBA_RED]   = static_cast<uint8_t>(255.0f * c.R);
            scanline[FI_RGBA_GREEN] = static_cast<uint8_t>(255.0f * c.G);
            scanline[FI_RGBA_BLUE]  = static_cast<uint8_t>(255.0f * c.B);
            scanline[FI_RGBA_ALPHA] = static_cast<uint8_t>(255.0f * c.A);
            scanline += bpp;
        }
    }

    Creates();
}

void Texture2D::Creates()
{
    DXGI_FORMAT pixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    UINT width = FreeImage_GetWidth(m_bitmap);
    UINT height = FreeImage_GetHeight(m_bitmap);
    
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

    BYTE* pbBuffer = FreeImage_GetBits(m_bitmap);
    UINT pitch = FreeImage_GetPitch(m_bitmap);
    
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = pbBuffer;
    data.SysMemPitch = pitch;
    data.SysMemSlicePitch = pitch * height;

    ID3D11Device* device = GlobalStaticReferences::Instance()->GetGraphicsDevice()->GetGraphicsDevice();
    HRESULT createTextureResult = device->CreateTexture2D(&desc, &data, m_pTexture);
    if (SUCCEEDED(createTextureResult))
    {
        ShaderResource* myShaderResourceView = GlobalStaticReferences::Instance()->GetTypedObjectManager()->Create<ShaderResource>();
		m_myShaderResourceViewIndex = static_cast<int>(myShaderResourceView->GetInstanceID());

        bool createdView = myShaderResourceView->CreateViewWithResource(m_pTexture, NULL);
        if (!createdView)
        {
			GlobalStaticReferences::Instance()->GetTypedObjectManager()->Delete<ShaderResource>(m_myShaderResourceViewIndex);
            LogError("Could not create resource view");
        }
    }
    else
    {
        LogError("Could not create texture");
    }
}

void Texture2D::Finalize()
{
    if (m_bitmap != nullptr)
    {
        FreeImage_Unload(m_bitmap);
    }
    m_pTexture.ReleasePointer();
}
