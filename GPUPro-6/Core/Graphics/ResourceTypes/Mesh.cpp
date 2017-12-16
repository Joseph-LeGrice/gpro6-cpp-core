#include "stdafx.h"
#include "Core/Graphics/ResourceTypes/Mesh.h"
#include "Core/ResourceManagement/AssetManager.h"


Mesh::Mesh(UINT resourceId) : IResource(resourceId)
{
	m_topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_indices = std::vector<UINT16>();
	m_vertexData = std::vector<VertexData>();
}

void Mesh::SetVertices(std::vector<Vector3>& verts)
{
	m_vertexData.resize(verts.size());
	for (size_t i = 0; i < verts.size(); ++i)
	{
		void* dst = &m_vertexData[i].vertexPosition;
		memcpy(dst, &verts.at(i), sizeof(Vector3));
	}
}

void Mesh::SetNormals(std::vector<Vector3>& normals)
{
	if (m_vertexData.size() == normals.size())
	{
		for (size_t i = 0; i < normals.size(); ++i)
		{
			void* dst = &m_vertexData[i].normal;
			memcpy(dst, &normals.at(i), sizeof(Vector3));
		}
	}
}

void Mesh::SetUVs(std::vector<Vector2>& uvs)
{
	if (m_vertexData.size() == uvs.size())
	{
		for (size_t i = 0; i < uvs.size(); ++i)
		{
			void* dst = &m_vertexData[i].uv;
			memcpy(dst, &uvs.at(i), sizeof(Vector2));
		}
	}
}

void Mesh::SetIndices(std::vector<UINT16>& indices)
{
	m_indices = indices;
}

const std::vector<VertexData>& Mesh::GetVertexData()
{
	return m_vertexData;
}

const std::vector<UINT16>& Mesh::GetIndices()
{
	return m_indices;
}

void Mesh::Release()
{
}
