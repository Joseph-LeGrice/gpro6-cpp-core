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
	std::vector<Vector3> verts;
	std::vector<UINT16> tris;

	for (unsigned int z = 0; z < sc_chunkSize - 1; z++)
	{
		for (unsigned int y = 0; y < sc_chunkSize - 1; y++)
		{
			for (unsigned int x = 0; x < sc_chunkSize - 1; x++)
			{
				unsigned int baseIndex = z * sc_chunkSize * sc_chunkSize + y * sc_chunkSize + x;

				int8_t corners[8] = {
					m_voxelValues[baseIndex],
					m_voxelValues[baseIndex + 1],
					m_voxelValues[baseIndex + sc_chunkSize * sc_chunkSize],
					m_voxelValues[baseIndex + sc_chunkSize * sc_chunkSize + 1],
					m_voxelValues[baseIndex + sc_chunkSize],
					m_voxelValues[baseIndex + sc_chunkSize + 1],
					m_voxelValues[baseIndex + sc_chunkSize + sc_chunkSize * sc_chunkSize],
					m_voxelValues[baseIndex + sc_chunkSize + sc_chunkSize * sc_chunkSize + 1]
				};

				uint8_t caseCode = 0;
				for (int i = 0; i < 8; i++) {
					caseCode |= (corners[i] >> (7 - i)) & (1 << i);
				}

				if ((caseCode ^ ((corners[7] >> 7) & 0xFF)) != 0) {
					unsigned int caseIndex = regularCellClass[caseCode];
					RegularCellData rcd = regularCellData[caseIndex];
					unsigned short* vertexData[12] = regularVertexData[caseCode];

					long l = rcd.GetTriangleCount();
					std::stringstream ss;
					ss << l;
					Log(ss.str());
				}
			}
		}
	}

	Mesh* m = GetResourceManager().Instantiate<Mesh>();
	m->SetVertices(verts);
	m->SetIndices(tris);
	m_meshResourceId = m->GetResourceID();
}
