#include "stdafx.h"
#include "RendererVolumetricExplosion.h"
#include "PerlinNoise.h"
#include "PositionUV_InputLayout.h"


RendererVolumetricExplosion::RendererVolumetricExplosion()
{
	m_pTexture = nullptr;
	m_inputLayout = new PositionUV_InputLayout();
}


RendererVolumetricExplosion::~RendererVolumetricExplosion()
{
	SAFE_DELETE(m_inputLayout);
}

Shader* RendererVolumetricExplosion::InitShaders(ID3D11Device* device)
{
	std::wstring filename = L"VolumetricExplosion.shader";
	Shader* s = new Shader();
	if (s->InitVertexShader(filename, "VShader", device, m_inputLayout) &&
		s->InitHullShader(filename, "HShader", device) &&
		s->InitDomainShader(filename, "DShader", device) &&
		s->InitGeometryShader(filename, "GShaderTessellation", device) &&
		s->InitPixelShader(filename, "SolidColorPShaderGeometry", device))
		//s->InitPixelShader(filename, "SolidColorPShader", device))
	{
		return s;
	}
	else
	{
		delete s;
		return nullptr;
	}
}

Mesh* RendererVolumetricExplosion::InitMesh(ID3D11Device* device)
{
	Mesh* m = new Mesh();
	m->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST);

	std::vector<Vertex> verts = std::vector<Vertex>({ { 0.0, 0.0, 0.0 } });
	bool setVerts = m->SetVertices(device, verts);
	
	std::vector<UINT16> indicies = std::vector<UINT16>({ { 0 } });
	bool setIndices = m->SetIndices(device, indicies);
	
	if (setVerts && setIndices && Init3DTexture(device, m))
	{
		return m;
	}
	else
	{
		delete m;
		return nullptr;
	}
}

struct COLOR_DATA
{
	FLOAT R;
};

bool RendererVolumetricExplosion::Init3DTexture(ID3D11Device* device, Mesh* m)
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

	if (device->CreateTexture3D(&desc, &data, &m_pTexture) == S_OK)
	{
		if (m->SetShaderResource(device, m_pTexture))
		{
			return true;
		}
	}

	SAFE_RELEASE(m_pTexture);
	delete[] color_data;
	return false;
}