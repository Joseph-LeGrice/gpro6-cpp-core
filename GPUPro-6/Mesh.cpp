#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh()
{
	m_topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
}

void Mesh::SetTopology(D3D_PRIMITIVE_TOPOLOGY t)
{
	m_topology = t;
}

void Mesh::SetVertices(std::vector<Vector3> verts)
{
	m_vertexData.resize(verts.size());
	for (size_t i = 0; i < verts.size(); ++i)
	{
		m_vertexData[i].vertexPosition = verts[i];
	}
}

void Mesh::SetNormals(std::vector<Vector3> normals)
{
	if (m_vertexData.size() == normals.size())
	{
		for (size_t i = 0; i < normals.size(); ++i)
		{
			m_vertexData[i].normal = normals[i];
		}
	}
}

void Mesh::SetUVs(std::vector<Vector2> uvs)
{
	if (m_vertexData.size() == uvs.size())
	{
		for (size_t i = 0; i < uvs.size(); ++i)
		{
			m_vertexData[i].uv = uvs[i];
		}
	}
}

void Mesh::SetIndices(std::vector<UINT16> indices)
{
	m_indices = indices;
}

const D3D_PRIMITIVE_TOPOLOGY Mesh::GetTopology()
{
	return m_topology;
}

const std::vector<VertexData> Mesh::GetVertices()
{
	return m_vertexData;
}

const std::vector<UINT16> Mesh::GetIndices()
{
	return m_indices;
}
