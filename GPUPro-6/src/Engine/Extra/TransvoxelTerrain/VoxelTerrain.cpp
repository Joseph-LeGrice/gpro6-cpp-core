#include "stdafx.h"
#include "VoxelTerrain.h"
#include "Engine/Core/Utilities/Noise.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Transvoxel.cpp"

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
    unsigned int m_vertexStartIndex;
    Vector3 m_vertices[4];
    bool m_verticesActive[4] = { false, false, false, false };
};

VoxelTerrain::VoxelTerrain()
{
	GenerateVoxelValues();
	GenerateMesh();
}

VoxelTerrain::~VoxelTerrain()
{
}

void VoxelTerrain::DeallocateMesh()
{
	GetResourceManager().Deallocate<Mesh>(m_meshResourceId);
}

Mesh* VoxelTerrain::GetMesh()
{
	return GetResourceManager().GetAsset<Mesh>(m_meshResourceId);
}

void VoxelTerrain::GenerateVoxelValues()
{
	float baseFrequency = 46;
	int numOctaves = 6;
	float lacunarity = 3.412f;
	float persistance = 0.02f;
	Noise::NoiseFuncConfig noiseConfig = { Noise::kNoiseTypePerlin, Noise::kNoiseDimension2D };

	for (unsigned int z = 0; z < sc_chunkSize; z++)
	{
		for (unsigned int y = 0; y < sc_chunkSize; y++)
		{
			for (unsigned int x = 0; x < sc_chunkSize; x++)
			{
				unsigned int index = z * sc_chunkSize * sc_chunkSize + y * sc_chunkSize + x;
				Vector3 position = {
					(((float)x + 0.5f) / sc_chunkSize) * 2.0f - 1.0f,
					(((float)y + 0.5f) / sc_chunkSize) * 2.0f - 1.0f,
					(((float)z + 0.5f) / sc_chunkSize) * 2.0f - 1.0f
				};
				//m_voxelValues[index] = Noise::FractalNoise(position, baseFrequency, noiseConfig, numOctaves, lacunarity, persistance);
				m_voxelValues[index] = (int8_t)floor(128.0f * Noise::FractalNoise(position, baseFrequency, noiseConfig, numOctaves, lacunarity, persistance)); // save some space this way?
			}
		}
	}
}

void VoxelTerrain::GenerateMesh()
{
    EndpointVertexData vertexData[sc_chunkSize * sc_chunkSize * sc_chunkSize];

    for (unsigned int z = 0; z < sc_chunkSize - 1; z++)
	{
		for (unsigned int y = 0; y < sc_chunkSize - 1; y++)
		{
			for (unsigned int x = 0; x < sc_chunkSize - 1; x++)
			{
				unsigned int voxelIndex = z * sc_chunkSize * sc_chunkSize + y * sc_chunkSize + x;

                unsigned int offsetIndexes[8] = {
                    0,
                    1,
                    sc_chunkSize * sc_chunkSize,
                    sc_chunkSize * sc_chunkSize + 1,
                    sc_chunkSize,
                    sc_chunkSize + 1,
                    sc_chunkSize + sc_chunkSize * sc_chunkSize,
                    sc_chunkSize + sc_chunkSize * sc_chunkSize + 1
                };

                int8_t corners[8] = {
					m_voxelValues[offsetIndexes[0]],
					m_voxelValues[offsetIndexes[1]],
					m_voxelValues[offsetIndexes[2]],
					m_voxelValues[offsetIndexes[3]],
					m_voxelValues[offsetIndexes[4]],
					m_voxelValues[offsetIndexes[5]],
					m_voxelValues[offsetIndexes[6]],
					m_voxelValues[offsetIndexes[7]]
				};

				uint8_t caseIndex = 0;
				for (int i = 0; i < 8; i++)
                {
					caseIndex |= (corners[i] >> (7 - i)) & (1 << i);
				}

				if ((caseIndex ^ ((corners[7] >> 7) & 0xFF)) != 0)
                {
					unsigned int classIndex = regularCellClass[caseIndex];
					RegularCellData rcd = regularCellData[classIndex];

                    //for (int i = 0; i < rcd.GetVertexCount(); i++)
                    //{
                    //    unsigned short vertexDataCode = regularVertexData[caseIndex][i];
                    //    // Create new Verts or reference old ones?
                    //}

                    for (int i = 0; i < rcd.GetTriangleCount(); i++) 
                    {
                        for (int ii = 0; ii < 3; ii++)
                        {
                            unsigned char vertexIndex = rcd.vertexIndex[i * 3 + ii];
                            unsigned short vertexDataCode = regularVertexData[caseIndex][vertexIndex];

                            //unsigned short dir = (vertexDataCode >> 12) & 0x000F;
                            //unsigned short index = (vertexDataCode >> 8) & 0x000F;
                            unsigned short v0 = (vertexDataCode >> 4) & 0x000F;
                            unsigned short v1 = vertexDataCode & 0x000F;

                            Vector3 p0 = vertexData[voxelIndex + v0].GetPosition();
                            Vector3 p1 = vertexData[voxelIndex + v1].GetPosition();

                            long d0 = corners[v0];
                            long d1 = corners[v1];

                            long t = (d1 << 8) / (d1 - d0);
                            if ((t & 0x0100) != 0) 
                            {
                                // Vertex lies in the interior of the edge. 
                                Log("Vertex lies in the interior of the edge.");

                                //long u = 0x0100 - t;
                                //Vector3 Q = p0 * t + p1 * u;
                                //vertexData[voxelIndex].SetVertexPosition(index, Q);
                            }
                            else if (t == 0)
                            {
                                // Vertex lies at the higher-numbered endpoint. 
                                Log("Vertex lies at the higher-numbered endpoint.");
                                if (v1 == 7)
                                {
                                    // This cell owns the vertex. 
                                    Log("This cell owns the vertex.");
                                }
                                else
                                {
                                    // Try to reuse corner vertex from a preceding cell. 
                                    Log("Try to reuse corner vertex from a preceding cell.");
                                }
                            }
                            else 
                            {
                                // Vertex lies at the lower-numbered endpoint. 
                                Log("Vertex lies at the lower-numbered endpoint.");
                                // Always try to reuse corner vertex from a preceding cell. 
                                Log("Always try to reuse corner vertex from a preceding cell.");
                            }
                        }
                    }
				}
			}
		}
	}

    std::vector<Vector3> verts;
    std::vector<UINT16> tris;

    Mesh* m = GetResourceManager().Instantiate<Mesh>();
	m->SetVertices(verts);
	m->SetIndices(tris);
	m_meshResourceId = m->GetResourceID();
}
