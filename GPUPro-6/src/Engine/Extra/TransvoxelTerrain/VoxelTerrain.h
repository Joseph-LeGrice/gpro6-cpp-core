#pragma once

class Mesh;

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
	int m_meshResourceId = -1;

	void GenerateVoxelValues();
	void GenerateMesh();
};