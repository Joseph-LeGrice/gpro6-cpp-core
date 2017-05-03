#include "stdafx.h"
#include "RendererVolumetricExplosion.h"
#include "PerlinNoise.h"
#include "PositionUV_InputLayout.h"
#include "VolumetricExplosionConstantBuffer.h"
#include "VolumetricExplosionResources.h"


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
	
	if (setVerts && setIndices)
	{
		return m;
	}
	else
	{
		delete m;
		return nullptr;
	}
}

ConstantBuffer* RendererVolumetricExplosion::InitConstantBuffer(ID3D11Device* device)
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

ResourceViews* RendererVolumetricExplosion::InitResourceViews(ID3D11Device* device)
{
	ResourceViews* res = new VolumetricExplosionResources();
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
