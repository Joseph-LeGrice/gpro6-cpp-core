#include "stdafx.h"
#include "MeshHelper.h"

#include <math.h>
#include "MathHelper.h"

Mesh MeshHelper::CreateQuad()
{
	Mesh result = Mesh::New();
	result.m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	std::vector<Vector3> verts = std::vector<Vector3>();
	verts.push_back({ -1.0f, -1.0f, 0.0f });
	verts.push_back({ -1.0f,  1.0f, 0.0f });
	verts.push_back({  1.0f,  1.0f, 0.0f });
	verts.push_back({  1.0f, -1.0f, 0.0f });
	result.SetVertices(result, verts);

	std::vector<Vector3> normals = std::vector<Vector3>();
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	result.SetNormals(result, normals);

	std::vector<Vector2> uvs = std::vector<Vector2>();
	uvs.push_back({ 0.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f });
	uvs.push_back({ 1.0f, 0.0f });
	uvs.push_back({ 1.0f, 1.0f });
	result.SetUVs(result, uvs);

	std::vector<UINT16> indices = std::vector<UINT16>();
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
	result.SetIndices(result, indices);

	return result;
}

Mesh MeshHelper::CreateSphereICO()
{
	Mesh result;

	std::vector<Vector3> verts = std::vector<Vector3>();
	std::vector<Vector3> norms = std::vector<Vector3>();
	std::vector<Vector2> uvs = std::vector<Vector2>();
	std::vector<UINT16> indices = std::vector<UINT16>();


	result.SetVertices(result, verts);
	result.SetNormals(result, norms);
	result.SetUVs(result, uvs);
	result.SetIndices(result, indices);

	return result;
}

Mesh MeshHelper::CreateSphereUV()
{
	Mesh result;
	result.m_topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::vector<Vector3> verts = std::vector<Vector3>();
	std::vector<Vector3> norms = std::vector<Vector3>();
	std::vector<Vector2> uvs = std::vector<Vector2>();
	std::vector<UINT16> indices = std::vector<UINT16>();

	float radius = 1.0f;
	size_t latitude = 8;
	size_t longitude = 9;

	for (size_t latSlice = 0; latSlice < latitude; ++latSlice)
	{
		float phi = (float)latSlice / (latitude - 1.0f) * PI;
		for (size_t lonSlice = 0; lonSlice < longitude; ++lonSlice)
		{
			float progression = (float)lonSlice / (longitude - 1.0f);
			float theta = progression * 2.0f * PI;

			float x = radius * cos(theta) * sin(phi);
			float y = radius * cos(phi); 
			float z = radius * sin(theta) * sin(phi);
			verts.push_back({ x, y, z });
			norms.push_back({ x, y, z });

			float u = (float)lonSlice / (longitude - 1.0f);
			float v = (float)latSlice / (latitude - 1.0f);
			uvs.push_back({ u, v });
		}
	}

	for (size_t latSlice = 0; latSlice < latitude - 1; ++latSlice)
	{
		for (size_t lonSlice = 0; lonSlice < longitude - 1; ++lonSlice)
		{
			int offset = latSlice * latitude;
			int v1 = lonSlice + offset;
			int v2 = lonSlice + 1 + offset;

			int nextOffset = (latSlice + 1) * latitude;
			int v3 = lonSlice + nextOffset;
			int v4 = lonSlice + 1 + nextOffset;

			indices.push_back(v1);
			indices.push_back(v2);
			indices.push_back(v3);

			indices.push_back(v2);
			indices.push_back(v4);
			indices.push_back(v3);
		}
	}

	result.SetVertices(result, verts);
	result.SetNormals(result, norms);
	result.SetUVs(result, uvs);
	result.SetIndices(result, indices);

	return result;
}

Mesh MeshHelper::CreateCube()
{
	Mesh result;
	result.m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::vector<Vector3> verts = std::vector<Vector3>();
	std::vector<Vector3> norms = std::vector<Vector3>();
	std::vector<Vector2> uvs = std::vector<Vector2>();
	std::vector<UINT16> indices = std::vector<UINT16>();

	// Front Face
	verts.push_back({ -1.0f,  1.0f, -1.0f });
	verts.push_back({  1.0f,  1.0f, -1.0f });
	verts.push_back({ -1.0f, -1.0f, -1.0f });
	verts.push_back({  1.0f, -1.0f, -1.0f });
	
	norms.push_back({ 0.0f, 0.0f, -1.0f });
	norms.push_back({ 0.0f, 0.0f, -1.0f });
	norms.push_back({ 0.0f, 0.0f, -1.0f });
	norms.push_back({ 0.0f, 0.0f, -1.0f });
	
	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	// Left Face
	verts.push_back({ -1.0f,  1.0f,  1.0f });
	verts.push_back({ -1.0f,  1.0f, -1.0f });
	verts.push_back({ -1.0f, -1.0f,  1.0f });
	verts.push_back({ -1.0f, -1.0f, -1.0f });

	norms.push_back({ -1.0f,  0.0f,  0.0f });
	norms.push_back({ -1.0f,  0.0f,  0.0f });
	norms.push_back({ -1.0f,  0.0f,  0.0f }); 
	norms.push_back({ -1.0f,  0.0f,  0.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(7);
	
	// Top Face
	verts.push_back({ -1.0f, 1.0f, -1.0f });
	norms.push_back({  0.0f,  0.0f,  0.0f }); 
	verts.push_back({  1.0f, 1.0f, -1.0f });
	verts.push_back({ -1.0f, 1.0f,  1.0f });
	verts.push_back({  1.0f, 1.0f,  1.0f });

	norms.push_back({ 0.0f, 1.0f,  0.0f });
	norms.push_back({ 0.0f, 1.0f,  0.0f });
	norms.push_back({ 0.0f, 1.0f,  0.0f });
	norms.push_back({ 0.0f, 1.0f,  0.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(10);
	indices.push_back(10);
	indices.push_back(9);
	indices.push_back(11);
	
	// Bottom Face
	verts.push_back({  1.0f, -1.0f, -1.0f });
	verts.push_back({ -1.0f, -1.0f, -1.0f });
	verts.push_back({  1.0f, -1.0f,  1.0f });
	verts.push_back({ -1.0f, -1.0f,  1.0f });

	norms.push_back({ 0.0f, -1.0f,  0.0f });
	norms.push_back({ 0.0f, -1.0f,  0.0f });
	norms.push_back({ 0.0f, -1.0f,  0.0f });
	norms.push_back({ 0.0f, -1.0f,  0.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(14);
	indices.push_back(13);
	indices.push_back(15);
	
	// Back Face
	verts.push_back({ -1.0f,  1.0f, 1.0f });
	verts.push_back({  1.0f,  1.0f, 1.0f });
	verts.push_back({ -1.0f, -1.0f, 1.0f });
	verts.push_back({  1.0f, -1.0f, 1.0f });

	norms.push_back({ 0.0f, 0.0f,  1.0f });
	norms.push_back({ 0.0f, 0.0f,  1.0f });
	norms.push_back({ 0.0f, 0.0f,  1.0f });
	norms.push_back({ 0.0f, 0.0f,  1.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(19);

	result.SetVertices(result, verts);
	result.SetNormals(result, norms);
	result.SetUVs(result, uvs);
	result.SetIndices(result, indices);
	return result;
}
