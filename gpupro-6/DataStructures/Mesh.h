#pragma once

#include "DataStructures\Matrix4x4.h"
#include "DataStructures\VertexData.h"
#include <vector>

class Mesh
{
public:
	D3D_PRIMITIVE_TOPOLOGY m_topology;

	Mesh();
	Mesh(const Mesh&) = delete;

	void SetVertices(std::vector<Vector3>& verts);
	void SetNormals(std::vector<Vector3>& normals);
	void SetUVs(std::vector<Vector2>& uvs);
	void SetIndices(std::vector<UINT16>& indices);

	const std::vector<VertexData>& GetVertexData();
	const std::vector<UINT16>& GetIndices();
	
private:
	std::vector<UINT16> m_indices;
	std::vector<VertexData> m_vertexData;
};
