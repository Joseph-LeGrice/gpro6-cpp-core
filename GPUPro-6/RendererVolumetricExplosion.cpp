#include "stdafx.h"
#include "RendererVolumetricExplosion.h"


RendererVolumetricExplosion::RendererVolumetricExplosion()
{
}


RendererVolumetricExplosion::~RendererVolumetricExplosion()
{
}

Shader* RendererVolumetricExplosion::InitShaders(ID3D11Device* device)
{
	std::wstring filename = L"VolumetricExplosion.shader";
	Shader* s = new Shader();
	if (s->InitVertexShader(filename, "VShader", device) &&
		s->InitHullShader(filename, "HShader", device) &&
		s->InitDomainShader(filename, "DShader", device) &&
		//s->InitGeometryShader(filename, "GShaderTessellation", device) &&
		//s->InitPixelShader(filename, "SolidColorPShaderGeometry", device))
		s->InitPixelShader(filename, "SolidColorPShader", device))
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
