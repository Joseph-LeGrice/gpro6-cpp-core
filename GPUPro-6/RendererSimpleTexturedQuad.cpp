#include "stdafx.h"
#include "RendererSimpleTexturedQuad.h"
#include "PerlinNoise.h"
#include "PositionUV_InputLayout.h"
#include "VolumetricExplosionConstantBuffer.h"
#include "SimpleTextureResources.h"


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

	if (m->SetVertices(device, verts) && m->SetIndices(device, indices))
	{
		return m;
	}
	else
	{
		SAFE_DELETE(m);
		return nullptr;
	}
}

ConstantBuffer* RendererSimpleTexturedQuad::InitConstantBuffer(ID3D11Device* device)
{
	ConstantBuffer* buf = new VolumetricExplosionConstantBuffer();
	if (buf->Initialize(device))
	{
		return buf;
	}
	else
	{
		SAFE_DELETE(buf);
		return nullptr;
	}
}

ResourceViews* RendererSimpleTexturedQuad::InitResourceViews(ID3D11Device* device)
{
	ResourceViews* res = new SimpleTextureResources();
	if (res->Initialize(device))
	{
		return res;
	}
	else
	{
		SAFE_DELETE(res);
		return nullptr;
	}
}
