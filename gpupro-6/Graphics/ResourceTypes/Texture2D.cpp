#include "stdafx.h"

#include "Graphics/ResourceTypes/Texture2D.h"
#include "SystemManagement/SystemManager.h"
#include "AssetManagement/AssetManager.h"
#include "Utilities/PerlinNoise.h"
#include "Utilities/ImagingFactory.h"

Texture2D::Texture2D()
{
	m_pTexture = nullptr;
	m_resourceView = nullptr;
}

Texture2D::~Texture2D()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_resourceView);
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

int Texture2D::CreateTextureResourceFromFile(std::wstring filepath)
{
    BYTE* pbBuffer = nullptr;
	UINT bpp, width, height;
	DXGI_FORMAT pixelFormat;
	HRESULT hr = ImagingFactory::GetPixelDataFromFile(filepath, &pbBuffer, pixelFormat, bpp, width, height);

	if (SUCCEEDED(hr))
	{
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
		data.SysMemPitch = width * bpp;
		data.SysMemSlicePitch = width * height * bpp;

        int index = GetAssetManager().AllocateNew<Texture2D>();
        Texture2D* newTexture2D = GetAssetManager().GetAsset<Texture2D>(index);
        
        ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
		bool createdEverything = false;
		HRESULT createTextureResult = device->CreateTexture2D(&desc, &data, &newTexture2D->m_pTexture);
		if (SUCCEEDED(createTextureResult))
		{
			HRESULT createResourceViewResult = device->CreateShaderResourceView(newTexture2D->m_pTexture, NULL, &newTexture2D->m_resourceView);
			if (SUCCEEDED(createResourceViewResult))
			{
				createdEverything = true;
			}
		}

		if (!createdEverything)
		{
            GetAssetManager().Deallocate<Texture2D>(index);
		}
		delete[] pbBuffer;

		return index;
	}
	else
	{
		return -1;
	}
}

/*

TODO: Reimplement this with COLOR_DATA being a bit more standardised somewhere else
	  Actually when we come back to this we could adopt more of a 'procedural texture' approach where we can update the texture at arbitrary points throughout runtime.

struct COLOR_DATA
{
	FLOAT R;
	FLOAT G;
	FLOAT B;
	FLOAT A;
}; 

Texture2D_ShaderResource Texture2D_ShaderResource::CreateFromData(COLOR_DATA[] data)
{
	ID3D11Device* device = SystemManagement::GetSystem<GraphicsSystem>()->GetGraphicsDevice();
	const int texture_size = 64;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	desc.Width = texture_size;
	desc.Height = texture_size;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	COLOR_DATA* color_data = new COLOR_DATA[texture_size * texture_size];

	//FIXME: Memory Leak here if something goes wrong?
	//for (int x = 0; x < texture_size; x++)
	//{
	//	for (int y = 0; y < texture_size; y++)
	//	{
	//		color_data[y * texture_size + x].R = x / 32.0f;
	//		color_data[y * texture_size + x].G = y / 32.0f;
	//		color_data[y * texture_size + x].B = 0.0f;
	//		color_data[y * texture_size + x].A = 1.0f;
	//	}
	//}

	for (int x = 0; x < texture_size; x++)
	{
		for (int y = 0; y < texture_size; y++)
		{
			double noiseVal = PerlinNoise::noise(
				(double)(x * 3.6 + 4 * texture_size * 2.75),
				(double)(y * 2.5 + 2 * texture_size * 232.75),
				(double)(x * y * texture_size * 23.45));
			noiseVal = noiseVal * 0.23 + noiseVal;
			//double noiseVal = PerlinNoise::octaveNoise(x, y, x*y, 4, 2.6);
			//double noiseVal = PerlinNoise::noise(x, y, x*y);

			color_data[y * texture_size + x].R = (FLOAT)noiseVal;
			color_data[y * texture_size + x].G = (FLOAT)noiseVal;
			color_data[y * texture_size + x].B = (FLOAT)noiseVal;
			color_data[y * texture_size + x].A = 1.0f;
		}
	}

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = color_data;
	data.SysMemPitch = sizeof(COLOR_DATA) * texture_size;
	data.SysMemSlicePitch = sizeof(COLOR_DATA) * texture_size * texture_size;

	bool createdEverything = false;
	HRESULT createTextureResult = device->CreateTexture2D(&desc, &data, &m_pTexture);
	if (SUCCEEDED(createTextureResult))
	{
		HRESULT createResourceViewResult = device->CreateShaderResourceView(m_pTexture, NULL, &m_resourceView);
		if (SUCCEEDED(createResourceViewResult))
		{
			createdEverything = true;
		}
	}

	if (!createdEverything)
	{
		SAFE_RELEASE(m_pTexture);
		SAFE_RELEASE(m_resourceView);
		delete[] color_data;
	}

	return createdEverything;
}
*/
