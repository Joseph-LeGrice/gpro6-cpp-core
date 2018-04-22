#pragma once

#include <unordered_map>
#include "Engine/Core/RTTI/RTTI.h"

class IndexBuffer;
class VertexBuffer;
class ResourceManager;
class Mesh;

struct MeshInfo
{
	size_t m_indexStart;
	size_t m_vertexStart;
	size_t m_indexCount;
	size_t m_vertexCount;
};

class MeshManager
{
public:
	MeshManager(IndexBuffer& indexBuffer,
		VertexBuffer& vertexBuffer,
		ResourceManager& resourceManager) :
		m_indexBuffer(indexBuffer),
		m_vertexBuffer(vertexBuffer),
		m_resourceManager(resourceManager) { }
	~MeshManager();

	void BindBuffers();
	void RegisterMesh(Mesh* m);
	void UnregisterMesh(Mesh* m);
	MeshInfo GetMapping(Mesh* m);

private:
	IndexBuffer& m_indexBuffer;
	VertexBuffer& m_vertexBuffer;
	ResourceManager& m_resourceManager;
	std::unordered_map<InstanceID, MeshInfo> m_meshInfoMapping;

	void RefreshBuffers();
};

