#pragma once

#include <vector>
#include "D3D11.h"
#include "Matrix4x4.h"

#include "Vector2.h"
#include "Vector3.h"
#include "PODArray.h"

struct VertexData
{
	Vector3 vertexPosition;
	Vector3 normal;
	Vector2 uv;
};

struct Mesh
{
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	PODArray<UINT16> m_indices;
	PODArray<VertexData> m_vertexData;

	static Mesh New()
	{
		Mesh m;
		m.m_indices = PODArray<UINT16>::New();
		m.m_vertexData = PODArray<VertexData>::New();
		m.m_topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		return m;
	}

	static void Mesh::Free(Mesh& m)
	{
		PODArray<UINT16>::Free(m.m_indices);
		PODArray<VertexData>::Free(m.m_vertexData);
	}

	static void Mesh::SetVertices(Mesh& m, std::vector<Vector3> verts)
	{
		PODArray<VertexData>::Resize(m.m_vertexData, verts.size());
		for (size_t i = 0; i < verts.size(); ++i)
		{
			void* dst = &m.m_vertexData[i].vertexPosition;
			memcpy(dst, &verts.at(i), sizeof(Vector3));
		}
	}

	static void Mesh::SetNormals(Mesh& m, std::vector<Vector3> normals)
	{
		if (PODArray<VertexData>::Size(m.m_vertexData) == normals.size())
		{
			for (size_t i = 0; i < normals.size(); ++i)
			{
				void* dst = &m.m_vertexData[i].normal;
				memcpy(dst, &normals.at(i), sizeof(Vector3));
			}
		}
	}

	static void Mesh::SetUVs(Mesh& m, std::vector<Vector2> uvs)
	{
		if (PODArray<VertexData>::Size(m.m_vertexData) == uvs.size())
		{
			for (size_t i = 0; i < uvs.size(); ++i)
			{
				void* dst = &m.m_vertexData[i].uv;
				memcpy(dst, &uvs.at(i), sizeof(Vector2));
			}
		}
	}

	static void Mesh::SetIndices(Mesh& m, std::vector<UINT16> indices)
	{
		PODArray<UINT16>::PopulateWithVector(m.m_indices, indices);
	}
};
