#pragma once

#include <vector>
#include "D3D11.h"
#include "Matrix4x4.h"

#include "Vector3.h"

struct VertexData
{
	Vector3 vertexPosition;
	Vector3 normal;
	Vector2 uv;
};

class Mesh
{
public:
	Mesh();

	void SetTopology(D3D_PRIMITIVE_TOPOLOGY t);
	void SetVertices(std::vector<Vector3> verts);
	void SetNormals(std::vector<Vector3> normals);
	void SetUVs(std::vector<Vector2> uvs);
	void SetIndices(std::vector<UINT16> indices);

	const D3D_PRIMITIVE_TOPOLOGY GetTopology();
	const std::vector<VertexData> GetVertices();
	const std::vector<UINT16> GetIndices();

private:
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	std::vector<Vector3> m_vertexPositions;
	std::vector<Vector3> m_normals;
	std::vector<Vector2> m_uvs;
	std::vector<UINT16> m_indices;
	std::vector<VertexData> m_vertexData;
};

struct MeshInfo
{
	Mesh m_mesh;
	Matrix4x4 m_transform;
};