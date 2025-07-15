#include "stdafx.h"
#include "VoxelTerrain.h"
#include "Engine/Core/Utilities/Noise.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/Mesh.h"
#include "Transvoxel.cpp"

VoxelTerrain::VoxelTerrain(TypedObjectManager& resourceManager) : m_typedObjectManager(resourceManager)
{
	GenerateVoxelValues();
	GenerateMesh();
}

VoxelTerrain::~VoxelTerrain()
{
}

void VoxelTerrain::DeallocateMesh()
{
	m_typedObjectManager.Delete<Mesh>(m_meshResourceId);
}

int VoxelTerrain::GetMeshID()
{
	return m_meshResourceId;
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
				m_voxelValues[index] = (int8_t)floor(128.0f * Noise::FractalNoise(position, baseFrequency, noiseConfig, numOctaves, lacunarity, persistance)); // save some space this way?
			}
		}
	}
}

void VoxelTerrain::GenerateMesh()
{
    std::stringstream ss;

    uint16_t baseVertexIndex = 0;
    std::vector<VoxelEndpointTriangle> tempTris;

    for (int z = 0; z < sc_chunkSize - 1; z++)
    {
        for (int y = 0; y < sc_chunkSize - 1; y++)
        {
            for (int x = 0; x < sc_chunkSize - 1; x++)
            {
                GetEndpoint(x, y, z).SetPosition({ (float)x, (float)y, (float)z });
            }
        }
    }

    for (int z = 0; z < sc_chunkSize - 1; z++)
    {
        for (int y = 0; y < sc_chunkSize - 1; y++)
        {
            for (int x = 0; x < sc_chunkSize - 1; x++)
            {
                GetEndpoint(x, y, z).SetStartIndex(baseVertexIndex);

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
                                    float dist = static_cast<float>(t) / 0x0100;
                                    ss << dist << std::endl;
                                    baseVertexIndex++;
                                    float u = 1.0f - dist;
                                    Vector3 Q = p0 * dist + p1 * u;
                                    GetEndpoint(x, y, z).SetVertexPosition(index, Q);
                                    tempTris.push_back({ x, y, z, index });
                                }
                                else
                                {
                                    int xOffset = (dir & 0x1) == 0x1 ? -1 : 0;
                                    int yOffset = (dir & 0x2) == 0x2 ? -1 : 0;
                                    int zOffset = (dir & 0x4) == 0x4 ? -1 : 0;
                                    tempTris.push_back({ x + xOffset, y + yOffset, z + zOffset, index });
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
                                    baseVertexIndex++;
                                    GetEndpoint(x, y, z).SetVertexPosition(index, p1);
                                    tempTris.push_back({ x, y, z, index });
                                }
                                else
                                {
                                    // Try to reuse corner vertex from a preceding cell. 
                                    ss << "Try to reuse corner vertex from a preceding cell." << std::endl;
                                    int xOffset = (dir & 0x1) == 0x1 ? -1 : 0;
                                    int yOffset = (dir & 0x2) == 0x2 ? -1 : 0;
                                    int zOffset = (dir & 0x4) == 0x4 ? -1 : 0;
                                    tempTris.push_back({ x + xOffset, y + yOffset, z + zOffset, index });
                                }
                            }
                            else
                            {
                                // Vertex lies at the lower-numbered endpoint. 
                                ss << "Vertex lies at the lower-numbered endpoint." << std::endl;
                                // Always try to reuse corner vertex from a preceding cell. 
                                ss << "Always try to reuse corner vertex from a preceding cell." << std::endl;
                                int xOffset = (dir & 0x1) == 0x1 ? -1 : 0;
                                int yOffset = (dir & 0x2) == 0x2 ? -1 : 0;
                                int zOffset = (dir & 0x4) == 0x4 ? -1 : 0;
                                tempTris.push_back({ x + xOffset, y + yOffset, z + zOffset, index });
                            }
                        }
                    }
                }
            }
        }
    }
    ss << "Number of verts: " << baseVertexIndex;
    Log(ss.str());

    std::vector<Vector3> verts;
    for (unsigned int i = 0; i < sizeof(m_vertexData) / sizeof(EndpointVertexData); i++)
    {
        EndpointVertexData& evd = m_vertexData[i];
        for (int v = 0; v < 4; v++)
        {
            if (evd.HasVertex(v))
            {
                verts.push_back(evd.GetVertexPosition(v));
            }
        }
    }

    std::vector<UINT16> tris;
    for (unsigned int i = 0; i < tempTris.size(); i++)
    {
        VoxelEndpointTriangle vet = tempTris[i];
        uint16_t trueVertexIndex = GetEndpoint(vet.x, vet.y, vet.z).GetTrueVertexIndex(vet.corner_index);
        tris.push_back(trueVertexIndex);
    }

    Mesh* m = m_typedObjectManager.Create<Mesh>();
	m->SetVertices(verts);
	m->SetIndices(tris);
	m_meshResourceId = static_cast<int>(m->GetInstanceID());
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

EndpointVertexData& VoxelTerrain::GetEndpoint(int voxelX, int voxelY, int voxelZ)
{
    unsigned int shiftedVoxelIndex = (voxelZ + 1) * (sc_chunkSize + 1) * (sc_chunkSize + 1) +
        (voxelY + 1) * (sc_chunkSize + 1) +
        voxelX + 1;
    return m_vertexData[shiftedVoxelIndex];
}

EndpointVertexData& VoxelTerrain::GetCornerEndpoint(int voxelX, int voxelY, int voxelZ, unsigned int corner)
{
    unsigned int shiftedVoxelIndex = (voxelZ + 1) * (sc_chunkSize + 1) * (sc_chunkSize + 1) +
        (voxelY + 1) * (sc_chunkSize + 1) +
        voxelX + 1;

    int x = corner % 2;
    int y = MyMath::FloorToInt((float)corner / 4);
    int z = MyMath::FloorToInt((float)corner / 2) % 2;

    return m_vertexData[ShiftVoxelIndex(shiftedVoxelIndex, x, y, z)];
}
