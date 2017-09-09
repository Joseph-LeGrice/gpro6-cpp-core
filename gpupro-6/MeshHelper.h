#pragma once

#include "Mesh.h"

class MeshHelper
{
public:
	MeshHelper() = delete;
	MeshHelper(const MeshHelper&) = delete;
	~MeshHelper() = delete;

	static Mesh CreateQuad();
	static Mesh CreateSphereICO();
	static Mesh CreateSphereUV();
	static Mesh CreateCube();
};

