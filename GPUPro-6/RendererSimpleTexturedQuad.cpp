#include "stdafx.h"
#include "RendererSimpleTexturedQuad.h"
#include "PerlinNoise.h"
#include "PositionUV_InputLayout.h"


RendererSimpleTexturedQuad::RendererSimpleTexturedQuad()
{
	m_pTexture = nullptr;
	m_inputLayout = new PositionUV_InputLayout();
}


RendererSimpleTexturedQuad::~RendererSimpleTexturedQuad()
{
	SAFE_DELETE(m_inputLayout);
	SAFE_RELEASE(m_pTexture);
}

Shader* RendererSimpleTexturedQuad::InitShaders(ID3D11Device* device)
{
	Shader* result = new Shader();
	if (result->InitVertexShader(L"SimpleTexturedQuad.shader", "VShader", device, m_inputLayout) &&
		result->InitPixelShader(L"SimpleTexturedQuad.shader", "PShader", device))
	{
		return result;
	}
	else
	{
		SAFE_DELETE(result);
		return nullptr;
	}
}

Mesh* RendererSimpleTexturedQuad::InitMesh(ID3D11Device* device)
{
	Mesh* m = new Mesh();
	m->SetTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	std::vector<Vertex> verts = std::vector<Vertex>({
		{ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f },
		{ -0.5f,  0.5f, 0.0f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f, 0.0f }
	});

	std::vector<UINT16> indices = std::vector<UINT16>({
		0, 2, 1,
		0, 3, 2
	});

	if (m->SetVertices(device, verts) && m->SetIndices(device, indices) && InitTexture(device, m))
	{
		return m;
	}
	else
	{
		SAFE_DELETE(m);
		return nullptr;
	}
}

struct COLOR_DATA
{
	FLOAT R;
	FLOAT G;
	FLOAT B;
	FLOAT A;
};

bool RendererSimpleTexturedQuad::InitTexture(ID3D11Device* device, Mesh* m)
{
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
	
	COLOR_DATA* color_data = new COLOR_DATA[texture_size * texture_size]; //FIXME: Memory Leak here if something goes wrong?
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

	if (device->CreateTexture2D(&desc, &data, &m_pTexture) == S_OK)
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
