#pragma once

#include <vector>
#include "D3D11.h"

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT u;
	FLOAT v;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Render(ID3D11DeviceContext* deviceContext);
	void SetTopology(D3D_PRIMITIVE_TOPOLOGY t);
	bool SetVertices(ID3D11Device* device, std::vector<Vertex> &verts);
	bool SetIndices(ID3D11Device* device, std::vector<UINT16> &indices);
	bool SetShaderTexture(ID3D11Device* device, ID3D11Texture2D* texture);

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	ID3D11ShaderResourceView* m_resource;
	unsigned int m_numberOfIndices;
	ID3D11SamplerState* m_sampleState;
};

