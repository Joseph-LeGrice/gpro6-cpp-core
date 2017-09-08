#include "stdafx.h"
#include "Mesh.h"

void Mesh::SetTopology(D3D_PRIMITIVE_TOPOLOGY t)
{
	m_topology = t;
}

void Mesh::SetVertices(std::vector<Vector3> verts)
{
	m_vertexPositions = verts;
}

void Mesh::SetNormals(std::vector<Vector3> normals)
{
	if (m_vertexPositions.size() == normals.size())
	{
		m_normals = normals;
	}
}

void Mesh::SetUVs(std::vector<Vector2> uvs)
{
	if (m_vertexPositions.size() == uvs.size())
	{
		m_uvs = uvs;
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
	m_vertexData = std::vector<VertexData>();
	for (size_t i = 0; i < m_vertexPositions.size(); ++i)
	{
		VertexData vd;
		ZeroMemory(&vd, sizeof(VertexData));

		vd.vertexPosition = m_vertexPositions[i];

		if (m_normals.size() == m_vertexPositions.size())
		{
			vd.normal = m_normals[i];
		}

		if (m_uvs.size() == m_vertexPositions.size())
		{
			vd.uv = m_uvs[i];
		}

		m_vertexData.push_back(vd);
	}
	return m_vertexData;
}

const std::vector<UINT16> Mesh::GetIndices()
{
	return m_indices;
}
