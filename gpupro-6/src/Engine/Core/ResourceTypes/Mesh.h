#pragma once

#include "Engine/Core/RTTI/ITypedObject.h"

#include "Engine/Core/Graphics/VertexData.h"
#include <vector>

enum D3D_PRIMITIVE_TOPOLOGY;


class Mesh : public ITypedObject
{
REGISTER_TYPE(Mesh);
public:
	D3D_PRIMITIVE_TOPOLOGY m_topology;

	Mesh();

	void SetVertices(std::vector<Vector3>& verts);
	void SetNormals(std::vector<Vector3>& normals);
	void SetUVs(std::vector<Vector2>& uvs);
	void SetIndices(std::vector<UINT16>& indices);

	const std::vector<VertexData>& GetVertexData();
	const std::vector<UINT16>& GetIndices();

    virtual void Finalize() override;

private:
	std::vector<UINT16> m_indices;
	std::vector<VertexData> m_vertexData;
};
