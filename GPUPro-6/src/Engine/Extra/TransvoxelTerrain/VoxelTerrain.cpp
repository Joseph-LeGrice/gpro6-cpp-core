#include "stdafx.h"
#include "VoxelTerrain.h"
#include "Engine/Core/Utilities/Noise.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Transvoxel.cpp"

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
    std::stringstream ss;

    for (unsigned int z = 0; z < sc_chunkSize - 1; z++)
	{
		for (unsigned int y = 0; y < sc_chunkSize - 1; y++)
		{
			for (unsigned int x = 0; x < sc_chunkSize - 1; x++)
			{
				unsigned int voxelIndex = z * sc_chunkSize * sc_chunkSize + y * sc_chunkSize + x;

                std::array<int8_t, 8> corners = GetCorners(voxelIndex);

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

                            unsigned short dir = (vertexDataCode >> 12) & 0x000F;
                            unsigned short index = (vertexDataCode >> 8) & 0x000F;
                            unsigned short v0 = (vertexDataCode >> 4) & 0x000F;
                            unsigned short v1 = vertexDataCode & 0x000F;

                            Vector3 p0 = GetCornerEndpoint(x, y, z, v0).GetPosition();
                            Vector3 p1 = GetCornerEndpoint(x, y, z, v1).GetPosition();

                            long d0 = corners[v0];
                            long d1 = corners[v1];

                            long t = (d1 << 8) / (d1 - d0);
                            if ((t & 0x00FF) != 0) 
                            {
                                // Vertex lies in the interior of the edge. 
                                ss << "Vertex lies in the interior of the edge." << std::endl;

                                if (dir == 0x8)
                                {
                                    //long u = 0x0100 - t;
                                    //Vector3 Q = p0 * t + p1 * u;
                                    //GetCornerEndpoint(x, y, z).SetVertexPosition(index, Q);
                                    //GetCornerEndpoint(x, y, z).GetTrueVertexIndex(index);
                                }
                                else
                                {
                                    int xOffset = (dir & 0x1) == 0x1 ? -1 : 0;
                                    int yOffset = (dir & 0x2) == 0x2 ? -1 : 0;
                                    int zOffset = (dir & 0x4) == 0x4 ? -1 : 0;
                                    GetEndpoint(x + xOffset, y + yOffset, z + zOffset).GetTrueVertexIndex(index);
                                }
                            }
                            else if (t == 0)
                            {
                                // Vertex lies at the higher-numbered endpoint. 
                                ss << "Vertex lies at the higher-numbered endpoint." << std::endl;
                                if (v1 == 7)
                                {
                                    // This cell owns the vertex. 
                                    ss << "This cell owns the vertex: " << dir << std::endl;

                                }
                                else
                                {
                                    // Try to reuse corner vertex from a preceding cell. 
                                    ss << "Try to reuse corner vertex from a preceding cell." << std::endl;
                                }
                            }
                            else 
                            {
                                // Vertex lies at the lower-numbered endpoint. 
                                ss << "Vertex lies at the lower-numbered endpoint." << std::endl;
                                // Always try to reuse corner vertex from a preceding cell. 
                                ss << "Always try to reuse corner vertex from a preceding cell." << std::endl;
                            }
                        }
                    }
				}
			}
		}
	}
    Log(ss.str());

    std::vector<Vector3> verts;
    std::vector<UINT16> tris;

    Mesh* m = GetResourceManager().Instantiate<Mesh>();
	m->SetVertices(verts);
	m->SetIndices(tris);
	m_meshResourceId = m->GetResourceID();
}

int VoxelTerrain::ShiftVoxelIndex(int voxelIndex, int xDelta, int yDelta, int zDelta)
{
    return voxelIndex + xDelta + 
        sc_chunkSize * yDelta +
        sc_chunkSize * sc_chunkSize * zDelta;
}

std::array<int8_t, 8> VoxelTerrain::GetCorners(unsigned int voxelIndex)
{
    std::array<int8_t, 8> corners = {
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 0, 0, 0)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 1, 0, 0)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 0, 0, 1)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 1, 0, 1)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 0, 1, 0)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 1, 1, 0)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 0, 1, 1)],
        m_voxelValues[ShiftVoxelIndex(voxelIndex, 1, 1, 1)],
    };
    return corners;
}

EndpointVertexData VoxelTerrain::GetEndpoint(unsigned int voxelX, unsigned int voxelY, unsigned int voxelZ)
{
    unsigned int shiftedVoxelIndex = (voxelZ + 1) * (sc_chunkSize + 1) * (sc_chunkSize + 1) +
        (voxelY + 1) * (sc_chunkSize + 1) +
        voxelX + 1;
    return m_vertexData[shiftedVoxelIndex];
}

EndpointVertexData VoxelTerrain::GetCornerEndpoint(unsigned int voxelX, unsigned int voxelY, unsigned int voxelZ, unsigned int corner)
{
    unsigned int shiftedVoxelIndex = (voxelZ + 1) * (sc_chunkSize + 1) * (sc_chunkSize + 1) +
        (voxelY + 1) * (sc_chunkSize + 1) +
        voxelX + 1;

    int x = corner % 2;
    int y = MyMath::FloorToInt((float)corner / 4);
    int z = MyMath::FloorToInt((float)corner / 2) % 2;

    return m_vertexData[ShiftVoxelIndex(shiftedVoxelIndex, x, y, z)];
}
