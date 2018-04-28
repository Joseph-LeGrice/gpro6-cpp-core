#include "stdafx.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

#include "D3D11.h"

Mesh::Mesh()
{
	m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
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

void Mesh::Finalize()
{
}
