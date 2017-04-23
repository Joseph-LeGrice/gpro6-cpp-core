#include "stdafx.h"
#include "RendererSimpleQuadTessellator.h"


RendererSimpleQuadTessellator::RendererSimpleQuadTessellator()
{
}


RendererSimpleQuadTessellator::~RendererSimpleQuadTessellator()
{
}

Shader* RendererSimpleQuadTessellator::InitShaders(ID3D11Device* device)
{
	Shader* shader = new Shader();

	std::wstring filename = L"QuadTessellation.shader";

	bool vertexShaderCompiled = shader->InitVertexShader(filename, "VShader", device);
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
		delete shader;
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