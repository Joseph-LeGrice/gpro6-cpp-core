#pragma once

#include <vector>
#include "D3D11.h"
#include "Matrix.h"

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

	void SetTopology(D3D_PRIMITIVE_TOPOLOGY t);
	void SetVertices(std::vector<Vertex> verts);
	void SetIndices(std::vector<UINT16> indices);
	//TODO: Mesh Normals
	const D3D_PRIMITIVE_TOPOLOGY GetTopology();
	const std::vector<Vertex> GetVertices();
	const std::vector<UINT16> GetIndices();

private:
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	std::vector<Vertex> m_vertices;
	std::vector<UINT16> m_indices;

	unsigned int m_numberOfIndices;
};

struct MeshInfo
{
	Mesh* m_mesh;
	Matrix4x4 m_transform;
};