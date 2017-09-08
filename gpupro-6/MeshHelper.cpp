#include "stdafx.h"
#include "MeshHelper.h"


Mesh MeshHelper::CreateQuad()
{
	Mesh result;
	result.SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	std::vector<Vector3> verts = std::vector<Vector3>();
	verts.push_back({ -1.0f, -1.0f, 0.0f });
	verts.push_back({ -1.0f,  1.0f, 0.0f });
	verts.push_back({  1.0f,  1.0f, 0.0f });
	verts.push_back({  1.0f, -1.0f, 0.0f });
	result.SetVertices(verts);

	std::vector<Vector3> normals = std::vector<Vector3>();
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	normals.push_back({ 0.0f, 0.0f, 1.0f });
	result.SetNormals(normals);

	std::vector<Vector2> uvs = std::vector<Vector2>();
	uvs.push_back({ 0.0f, 1.0f });
	uvs.push_back({ 0.0f, 0.0f });
	uvs.push_back({ 1.0f, 0.0f });
	uvs.push_back({ 1.0f, 1.0f });
	result.SetUVs(uvs);

	std::vector<UINT16> indices = std::vector<UINT16>();
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
	result.SetIndices(indices);

	return result;
}

Mesh MeshHelper::CreateSphere()
{
	Mesh result;
	return result;
}

Mesh MeshHelper::CreateCube()
{
	Mesh result;
	result.SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

	result.SetVertices(verts);
	result.SetNormals(norms);
	result.SetUVs(uvs);
	result.SetIndices(indices);
	return result;
}
