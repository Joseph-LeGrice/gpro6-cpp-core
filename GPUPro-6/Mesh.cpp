#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	SAFE_DELETE(m_vertices);
	SAFE_DELETE(m_indices);
}

void Mesh::SetTopology(D3D_PRIMITIVE_TOPOLOGY t)
{
	m_topology = t;
}

void Mesh::SetVertices(std::vector<Vertex>** verts)
{
	m_vertices = *verts;
}

void Mesh::SetIndices(std::vector<UINT16>** indices)
{
	m_indices = *indices;
}

const D3D_PRIMITIVE_TOPOLOGY Mesh::GetTopology()
{
	return m_topology;
}

const std::vector<Vertex>* Mesh::GetVertices()
{
	return m_vertices;
}

const std::vector<UINT16>* Mesh::GetIndices()
{
	return m_indices;
}
