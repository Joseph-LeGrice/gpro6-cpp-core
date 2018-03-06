#pragma once

#include <array>

class Mesh;

struct EndpointVertexData
{
    EndpointVertexData() {

    }

    void SetStartIndex(int vertexIndex) {
        m_vertexStartIndex = vertexIndex;
    }

    void SetVertexPosition(int vertexIndex, Vector3 value) {
        custom_assert::range(vertexIndex, 0, 4);
        m_vertices[vertexIndex] = value;
        m_verticesActive[vertexIndex] = true;
    }

    unsigned int GetTrueVertexIndex(int vertexIndex) const {
        custom_assert::range(vertexIndex, 0, 4);
        int inc = 0;
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

    Vector3 GetPosition() const {
        return m_position;
    }

private:
    Vector3 m_position;
    Vector3 m_vertices[4];
    bool m_verticesActive[4] = { false, false, false, false };
    unsigned int m_vertexStartIndex;
};

class VoxelTerrain
{
public:
	VoxelTerrain();
	~VoxelTerrain();

	void DeallocateMesh();
	Mesh* GetMesh();

private:
	static const unsigned int sc_chunkSize = 32;
	int8_t m_voxelValues[sc_chunkSize * sc_chunkSize * sc_chunkSize];
    EndpointVertexData m_vertexData[(sc_chunkSize + 1) * (sc_chunkSize + 1) * (sc_chunkSize + 1)];

	int m_meshResourceId = -1;

	void GenerateVoxelValues();
	void GenerateMesh();

    EndpointVertexData GetEndpoint(unsigned int voxelX, unsigned int voxelY, unsigned int voxelZ);
    EndpointVertexData GetCornerEndpoint(unsigned int voxelX, unsigned int voxelY, unsigned int voxelZ, unsigned int corner);
    int ShiftVoxelIndex(int voxelIndex, int xDelta, int yDelta, int zDelta);
    std::array<int8_t, 8> GetCorners(unsigned int voxelIndex);
};