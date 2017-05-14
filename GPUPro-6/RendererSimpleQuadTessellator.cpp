#include "stdafx.h"
#include "RendererSimpleQuadTessellator.h"
#include "PositionUV_InputLayout.h"
#include "VolumetricExplosionConstantBuffer.h"


RendererSimpleQuadTessellator::RendererSimpleQuadTessellator()
{
	m_inputLayout = new PositionUV_InputLayout();
}


RendererSimpleQuadTessellator::~RendererSimpleQuadTessellator()
{
	SAFE_DELETE(m_inputLayout);
}

ResourceViews* RendererSimpleQuadTessellator::InitResourceViews(ID3D11Device* device)
{
	return nullptr;
}

ConstantBuffer* RendererSimpleQuadTessellator::InitConstantBuffer(ID3D11Device* device)
{
	VolumetricExplosionConstantBuffer* buf = new VolumetricExplosionConstantBuffer();
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

Shader* RendererSimpleQuadTessellator::InitShaders(ID3D11Device* device)
{
	Shader* shader = new Shader();
	std::wstring filename = L"QuadTessellation.shader";
	bool vertexShaderCompiled = shader->InitVertexShader(filename, "VShader", device, m_inputLayout);
	bool hullShaderCompiled = shader->InitHullShader(filename, "HShader", device);
	bool domainShaderCompiled = shader->InitDomainShader(filename, "DShader", device);
	bool geometryShaderCompiled = shader->InitGeometryShader(filename, "GShaderTessellation", device);
	bool pixelShaderCompiled = shader->InitPixelShader(filename, "SolidColorPShaderGeometry", device);

	if (vertexShaderCompiled && hullShaderCompiled && domainShaderCompiled && geometryShaderCompiled && pixelShaderCompiled)
	{
		return shader;
	}
	else
	{
		SAFE_DELETE(shader);
		return nullptr;
	}
}

Mesh* RendererSimpleQuadTessellator::InitMesh(ID3D11Device* device)
{
	std::vector<Vertex> verts;
	verts.push_back({ -0.5f, -0.5f, 0.0f });
	verts.push_back({ -0.5f,  0.5f, 0.0f });
	verts.push_back({ 0.5f,  0.5f, 0.0f });
	verts.push_back({ 0.5f, -0.5f, 0.0f });

	std::vector<UINT16> indices;

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	Mesh* mesh = new Mesh();
	mesh->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	if (mesh->SetVertices(device, verts) &&
		mesh->SetIndices(device, indices))
	{
		return mesh;
	}
	else
	{
		delete mesh;
		return nullptr;
	}
}