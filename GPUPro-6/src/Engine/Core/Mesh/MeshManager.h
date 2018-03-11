#pragma once

#include <unordered_map>

class IndexBuffer;
class VertexBuffer;
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
	MeshManager(IndexBuffer* indexBuffer,
		VertexBuffer* vertexBuffer) :
		m_indexBuffer(indexBuffer),
		m_vertexBuffer(vertexBuffer) { }
	~MeshManager();

	void BindBuffers();
	void RegisterMesh(Mesh* m);
	void UnregisterMesh(Mesh* m);
	MeshInfo GetMapping(Mesh* m);

private:
	IndexBuffer* m_indexBuffer;
	VertexBuffer* m_vertexBuffer;
	std::unordered_map<int, MeshInfo> m_meshInfoMapping;

	void RefreshBuffers();
};

