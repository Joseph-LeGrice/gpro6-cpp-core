#include "stdafx.h"
#include "RendererSimpleTexturedQuad.h"
#include "PerlinNoise.h"

RendererSimpleTexturedQuad::RendererSimpleTexturedQuad()
{
	m_pTexture = nullptr;
}


RendererSimpleTexturedQuad::~RendererSimpleTexturedQuad()
{
	SAFE_RELEASE(m_pTexture);
}

Shader* RendererSimpleTexturedQuad::InitShaders(ID3D11Device* device)
{
	Shader* result = new Shader();
	if (result->InitVertexShader(L"SimpleTexturedQuad.shader", "VShader", device) &&
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
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	desc.Width = 32;
	desc.Height = 32;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	
	COLOR_DATA* color_data = new COLOR_DATA[32*32]; //FIXME: Memory Leak here if something goes wrong?
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			color_data[y * 32 + x].R = 1.0f;
			color_data[y * 32 + x].G = 1.0f;
			color_data[y * 32 + x].B = 0.0f;
			color_data[y * 32 + x].A = 1.0f;
		}
	}

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = color_data;
	data.SysMemPitch = sizeof(COLOR_DATA) * 32;
	data.SysMemSlicePitch = sizeof(COLOR_DATA) * 32 * 32;

	if (device->CreateTexture2D(&desc, &data, &m_pTexture) == S_OK)
	{
		if (m->SetShaderTexture(device, m_pTexture))
		{
			return true;
		}
	}
	
	SAFE_RELEASE(m_pTexture);
	delete[] color_data;
	return false;
}
