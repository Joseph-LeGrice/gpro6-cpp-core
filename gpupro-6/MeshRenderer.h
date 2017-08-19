#pragma once
#include "Renderer.h"
class MeshRenderer :
	public Renderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void SetMesh(Mesh* mesh);

private:
	Mesh* m_mesh;
};

