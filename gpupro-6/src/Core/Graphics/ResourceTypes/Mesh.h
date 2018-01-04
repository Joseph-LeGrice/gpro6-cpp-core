#pragma once

#include "Core/ResourceManagement/IResource.h"
#include "Matrix/Matrix4x4.h"
#include "Core/Graphics/VertexData.h"
#include <vector>

class Mesh : public IResource
{
public:
	D3D_PRIMITIVE_TOPOLOGY m_topology;

	Mesh(UINT resourceId);

	void SetVertices(std::vector<Vector3>& verts);
	void SetNormals(std::vector<Vector3>& normals);
	void SetUVs(std::vector<Vector2>& uvs);
	void SetIndices(std::vector<UINT16>& indices);

	const std::vector<VertexData>& GetVertexData();
	const std::vector<UINT16>& GetIndices();

    virtual void Release() override;


private:
	std::vector<UINT16> m_indices;
	std::vector<VertexData> m_vertexData;
};
