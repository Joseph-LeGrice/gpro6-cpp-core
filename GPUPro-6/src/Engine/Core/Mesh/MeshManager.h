#pragma once

#include <unordered_map>
#include "Engine/Core/RTTI/RTTI.h"

class IndexBuffer;
class VertexBuffer;
class TypedObjectManager;
class Mesh;

struct MeshInfo
{
	unsigned int m_indexStart;
	unsigned int m_vertexStart;
	unsigned int m_indexCount;
	unsigned int m_vertexCount;
};

class MeshManager
{
public:
	MeshManager(IndexBuffer& indexBuffer,
		VertexBuffer& vertexBuffer,
		TypedObjectManager& resourceManager) :
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
	TypedObjectManager& m_resourceManager;
	std::unordered_map<InstanceID, MeshInfo> m_meshInfoMapping;

	void RefreshBuffers();
};

