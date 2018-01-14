#include "stdafx.h"

#include "Texture2DArray.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "Engine/Core/Utilities/Logging.h"

Texture2DArray::Texture2DArray(UINT resourceId) : IResource(resourceId)
{
    m_pTextureArray = nullptr;
    m_resourceView = nullptr;
}


Texture2DArray::~Texture2DArray()
{
}


void Texture2DArray::InitializeWithBitmaps(std::vector<std::wstring> filepaths)
{
    Release();

    for (size_t filepathIndex = 0; filepathIndex < filepaths.size(); filepathIndex++)
    {
        std::wstring thisFilepath = filepaths[filepathIndex];
        FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeU(thisFilepath.c_str());
        if (fif != FIF_UNKNOWN)
        {
            FIBITMAP* bmp = FreeImage_LoadU(fif, thisFilepath.c_str());
            m_bitmaps.push_back(FreeImage_ConvertTo32Bits(bmp));
            FreeImage_Unload(bmp);
        }
        else
        {
            LogError("Could not load bitmap FREE_IMAGE_FORMAT == FIF_UNKNOWN");
            Release();
            break;
        }
    }

    if (m_bitmaps.size() == filepaths.size())
    {
        FIBITMAP* firstBitmap = m_bitmaps[0];
        UINT pitch = FreeImage_GetPitch(firstBitmap);
        UINT width = FreeImage_GetWidth(firstBitmap);
        UINT height = FreeImage_GetHeight(firstBitmap);

        bool dimensionsMatch = true;
        for (size_t bitmapIndex = 1; bitmapIndex < m_bitmaps.size(); bitmapIndex++)
        {
            FIBITMAP* thisBitmap = m_bitmaps[bitmapIndex];
            UINT thisWidth = FreeImage_GetWidth(thisBitmap);
            UINT thisHeight = FreeImage_GetHeight(thisBitmap);
            dimensionsMatch = thisWidth == width && thisHeight == height;
        }

        if (dimensionsMatch)
        {
            CreateResources(pitch, width, height);
        }
        else
        {
            LogError("Dimensions of bitmaps in the array are not consistent");
            Release();
        }
    }
}

void Texture2DArray::CreateResources(UINT pitch, UINT width, UINT height)
{
    UINT arraySize = static_cast<UINT>(m_bitmaps.size());
    DXGI_FORMAT pixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = arraySize;
    desc.Format = pixelFormat;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    //TODO: Create separate TextureCube IResource class
    desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
    
    std::vector<D3D11_SUBRESOURCE_DATA> data;
    for (size_t i = 0; i < arraySize; i++)
    {
        BYTE* theseBytes = FreeImage_GetBits(m_bitmaps[i]);

        D3D11_SUBRESOURCE_DATA thisData;
        thisData.pSysMem = theseBytes;
        thisData.SysMemPitch = pitch;
        thisData.SysMemSlicePitch = pitch * height;
        data.push_back(thisData);
    }

    ID3D11Device* device = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDevice();
    HRESULT createTextureResult = device->CreateTexture2D(&desc, data.data(), m_pTextureArray);
    if (SUCCEEDED(createTextureResult))
    {
        HRESULT createResourceViewResult = device->CreateShaderResourceView(m_pTextureArray, NULL, m_resourceView);
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

void Texture2DArray::BindResource(UINT resourceIndex)
{
    ID3D11DeviceContext* deviceContext = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->VSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->HSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->DSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->GSSetShaderResources(resourceIndex, 1, m_resourceView);
    deviceContext->PSSetShaderResources(resourceIndex, 1, m_resourceView);
}

void Texture2DArray::Release()
{
    for (size_t i = 0; i < m_bitmaps.size(); i++)
    {
        FreeImage_Unload(m_bitmaps[i]);
    }
    m_bitmaps.clear();
    m_pTextureArray.ReleasePointer();
    m_resourceView.ReleasePointer();
}