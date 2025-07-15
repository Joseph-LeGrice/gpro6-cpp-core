#pragma once

#include <array>

class Mesh;
class TypedObjectManager;

struct EndpointVertexData
{
    EndpointVertexData() {
        m_vertexStartIndex = 0;
    }

    void SetStartIndex(uint16_t vertexIndex) {
        m_vertexStartIndex = vertexIndex;
    }

    void SetVertexPosition(int vertexIndex, Vector3 value) {
        custom_assert::range(vertexIndex, 0, 4);
        m_vertices[vertexIndex] = value;
        m_verticesActive[vertexIndex] = true;
    }

    uint16_t GetTrueVertexIndex(int vertexIndex) const {
        custom_assert::range(vertexIndex, 0, 4);
        uint16_t inc = 0;
        for (int i = 0; i < 4; i++)
        {
            if (m_verticesActive[i])
            {
                inc++;
            }
        }
        return m_vertexStartIndex + inc;
    }
    
    bool HasVertex(int vertexIndex) const {
        custom_assert::range(vertexIndex, 0, 4);
        return m_verticesActive[vertexIndex];
    }

    Vector3 GetVertexPosition(int vertexIndex) const {
        custom_assert::range(vertexIndex, 0, 4);
        custom_assert::is_true(m_verticesActive[vertexIndex]);
        return m_vertices[vertexIndex];
    }

    void SetPosition(Vector3 pos) {
        m_position = pos;
    }

    Vector3 GetPosition() const {
        return m_position;
    }

private:
    Vector3 m_position;
    Vector3 m_vertices[4];
    bool m_verticesActive[4] = { false, false, false, false };
    uint16_t m_vertexStartIndex;
};

struct VoxelEndpointTriangle
{
    int x, y, z;
    uint16_t corner_index;
};

class VoxelTerrain
{
public:
	VoxelTerrain(TypedObjectManager& resourceManager);
	~VoxelTerrain();

	void DeallocateMesh();
	int GetMeshID();

private:
	static const unsigned int sc_chunkSize = 16;
	TypedObjectManager& m_typedObjectManager;
	int8_t m_voxelValues[sc_chunkSize * sc_chunkSize * sc_chunkSize];
    EndpointVertexData m_vertexData[(sc_chunkSize + 1) * (sc_chunkSize + 1) * (sc_chunkSize + 1)];

	int m_meshResourceId = -1;

	void GenerateVoxelValues();
	void GenerateMesh();

    EndpointVertexData& GetEndpoint(int voxelX, int voxelY, int voxelZ);
    EndpointVertexData& GetCornerEndpoint(int voxelX, int voxelY, int voxelZ, unsigned int corner);
    int ShiftVoxelIndex(int voxelIndex, int xDelta, int yDelta, int zDelta);
    std::array<int8_t, 8> GetCorners(unsigned int voxelIndex);
};