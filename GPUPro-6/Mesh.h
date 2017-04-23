#pragma once

#include <vector>
#include "D3D11.h"

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
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

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	unsigned int m_numberOfIndices;
};

