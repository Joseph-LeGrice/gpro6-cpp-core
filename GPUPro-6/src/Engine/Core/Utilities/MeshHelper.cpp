#include "stdafx.h"
#include "MeshHelper.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "MyMath/MathDefines.h"

#include <math.h>

Mesh* MeshHelper::CreateQuad()
{
    Mesh* result = GetResourceManager().Instantiate<Mesh>();
	result->m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::vector<Vector3> verts = std::vector<Vector3>();
	verts.push_back({ -1.0f, -1.0f, 0.0f });
	verts.push_back({ -1.0f,  1.0f, 0.0f });
	verts.push_back({  1.0f,  1.0f, 0.0f });
	verts.push_back({  1.0f, -1.0f, 0.0f });
	result->SetVertices(verts);
		
	std::vector<Vector3> normals = std::vector<Vector3>();
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	result->SetNormals(normals);

	std::vector<Vector2> uvs = std::vector<Vector2>();
	uvs.push_back({ 0.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f });
	uvs.push_back({ 1.0f, 0.0f });
	uvs.push_back({ 1.0f, 1.0f });
	result->SetUVs(uvs);

	std::vector<UINT16> indices = std::vector<UINT16>();
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
    indices.push_back(2);
	indices.push_back(3);
    indices.push_back(1);
	result->SetIndices(indices);

	return result;
}

Mesh* MeshHelper::CreateSphereICO()
{
    std::vector<Vector3> verts = std::vector<Vector3>();
	std::vector<Vector3> norms = std::vector<Vector3>();
	std::vector<Vector2> uvs = std::vector<Vector2>();
	std::vector<UINT16> indices = std::vector<UINT16>();

    Mesh* result = GetResourceManager().Instantiate<Mesh>();
    result->SetVertices(verts);
    result->SetNormals(norms);
    result->SetUVs(uvs);
    result->SetIndices(indices);

	return result;
}

Mesh* MeshHelper::CreateSphereUV()
{
	std::vector<Vector3> verts = std::vector<Vector3>();
	std::vector<Vector3> norms = std::vector<Vector3>();
	std::vector<Vector2> uvs = std::vector<Vector2>();
	std::vector<UINT16> indices = std::vector<UINT16>();

	float radius = 1.0f;
	size_t latitude = 16;
	size_t longitude = 16;

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
			float v = 1.0f - (float)latSlice / (latitude - 1.0f);
			uvs.push_back({ u, v });
		}
	}

	for (size_t latSlice = 0; latSlice < latitude - 1; ++latSlice)
	{
		for (size_t lonSlice = 0; lonSlice < longitude - 1; ++lonSlice)
		{
			UINT16 offset = (UINT16)(latSlice * latitude);
			UINT16 v1 = (UINT16)(lonSlice + offset);
			UINT16 v2 = (UINT16)(lonSlice + 1 + offset);

			UINT16 nextOffset = (UINT16)((latSlice + 1) * latitude);
			UINT16 v3 = (UINT16)(lonSlice + nextOffset);
			UINT16 v4 = (UINT16)(lonSlice + 1 + nextOffset);

			indices.push_back(v1);
			indices.push_back(v2);
			indices.push_back(v3);

			indices.push_back(v3);
			indices.push_back(v2);
			indices.push_back(v4);
		}
	}

    Mesh* result = GetResourceManager().Instantiate<Mesh>();
    result->m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    result->SetVertices(verts);
    result->SetNormals(norms);
    result->SetUVs(uvs);
    result->SetIndices(indices);

	return result;
}

Mesh* MeshHelper::CreateCube()
{
	std::vector<Vector3> verts = std::vector<Vector3>();
	std::vector<Vector3> norms = std::vector<Vector3>();
	std::vector<Vector2> uvs = std::vector<Vector2>();
	std::vector<UINT16> indices = std::vector<UINT16>();

	// Front Face
	verts.push_back({ -1.0f,  1.0f, -1.0f });
	verts.push_back({ 1.0f,  1.0f, -1.0f });
	verts.push_back({ -1.0f, -1.0f, -1.0f });
	verts.push_back({ 1.0f, -1.0f, -1.0f });

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
	verts.push_back({ -1.0f, 1.0f,  1.0f });
	verts.push_back({  1.0f, 1.0f,  1.0f });
	verts.push_back({ -1.0f, 1.0f, -1.0f });
	verts.push_back({  1.0f, 1.0f, -1.0f });

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

	// Left Face
	verts.push_back({  1.0f, -1.0f,  1.0f });
	verts.push_back({  1.0f, -1.0f, -1.0f });
	verts.push_back({  1.0f,  1.0f,  1.0f });
	verts.push_back({  1.0f,  1.0f, -1.0f });

	norms.push_back({ -1.0f,  0.0f,  0.0f });
	norms.push_back({ -1.0f,  0.0f,  0.0f });
	norms.push_back({ -1.0f,  0.0f,  0.0f });
	norms.push_back({ -1.0f,  0.0f,  0.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(14);
	indices.push_back(13);
	indices.push_back(15);
	
	// Bottom Face
	verts.push_back({  1.0f, -1.0f,  1.0f });
	verts.push_back({ -1.0f, -1.0f,  1.0f });
	verts.push_back({  1.0f, -1.0f, -1.0f });
	verts.push_back({ -1.0f, -1.0f, -1.0f });

	norms.push_back({ 0.0f, -1.0f,  0.0f });
	norms.push_back({ 0.0f, -1.0f,  0.0f });
	norms.push_back({ 0.0f, -1.0f,  0.0f });
	norms.push_back({ 0.0f, -1.0f,  0.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(19);

	// Back Face
	verts.push_back({ -1.0f, -1.0f, 1.0f });
	verts.push_back({  1.0f, -1.0f, 1.0f });
	verts.push_back({ -1.0f,  1.0f, 1.0f });
	verts.push_back({  1.0f,  1.0f, 1.0f });

	norms.push_back({ 0.0f, 0.0f,  1.0f });
	norms.push_back({ 0.0f, 0.0f,  1.0f });
	norms.push_back({ 0.0f, 0.0f,  1.0f });
	norms.push_back({ 0.0f, 0.0f,  1.0f });

	uvs.push_back({ 0.0f, 1.0f }); uvs.push_back({ 1.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f }); uvs.push_back({ 1.0f, 0.0f });

	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(22);
	indices.push_back(22);
	indices.push_back(21);
	indices.push_back(23);

    Mesh* result = GetResourceManager().Instantiate<Mesh>();
    result->m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    result->SetVertices(verts);
    result->SetNormals(norms);
    result->SetUVs(uvs);
    result->SetIndices(indices);

	return result;
}
