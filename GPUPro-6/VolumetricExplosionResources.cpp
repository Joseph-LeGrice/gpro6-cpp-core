#include "stdafx.h"
#include "VolumetricExplosionResources.h"
#include "PerlinNoise.h"

VolumetricExplosionResources::VolumetricExplosionResources()
{
	m_pTexture = nullptr;
	m_resources = new std::vector<ID3D11ShaderResourceView *>();
}


VolumetricExplosionResources::~VolumetricExplosionResources()
{
	SAFE_RELEASE(m_pTexture);

	for (ID3D11ShaderResourceView* rv : *m_resources)
	{
		SAFE_RELEASE(rv);
	}
	SAFE_DELETE(m_resources);
}

struct COLOR_DATA
{
	FLOAT R;
};

bool VolumetricExplosionResources::Initialize(ID3D11Device* device)
{
	const int texture_size = 32;

	D3D11_TEXTURE3D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE3D_DESC));

	desc.Width = texture_size;
	desc.Height = texture_size;
	desc.Depth = texture_size;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R32_FLOAT;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	COLOR_DATA* color_data = new COLOR_DATA[texture_size * texture_size * texture_size];
	for (int x = 0; x < texture_size; x++)
	{
		for (int y = 0; y < texture_size; y++)
		{
			for (int z = 0; z < texture_size; z++)
			{
				FLOAT noiseVal = (FLOAT)PerlinNoise::noise(
					(double)(x * 3.6 + 4 * texture_size * 2.75),
					(double)(y * 2.5 + 2 * texture_size * 232.75),
					(double)(x * y * texture_size * 23.45)
					);

				int index = z * texture_size + y * texture_size + x;
				color_data[index].R = noiseVal;
			}
		}
	}

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = color_data;
	data.SysMemPitch = sizeof(COLOR_DATA) * texture_size;
	data.SysMemSlicePitch = sizeof(COLOR_DATA) * texture_size * texture_size;

	ID3D11ShaderResourceView* resourceView;

	if (device->CreateTexture3D(&desc, &data, &m_pTexture) == S_OK && device->CreateShaderResourceView(m_pTexture, NULL, &resourceView) == S_OK)
	{
		m_resources->push_back(resourceView);

		return true;
	}
	else
	{
		SAFE_RELEASE(m_pTexture);
		SAFE_RELEASE(resourceView);
		delete[] color_data;

		return false;
	}
}

std::vector<ID3D11ShaderResourceView *>* VolumetricExplosionResources::GetPSResources()
{
	return m_resources;
}
