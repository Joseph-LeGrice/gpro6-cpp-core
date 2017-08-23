#pragma once
#include "Renderer.h"

struct MeshInfo;

class MeshRenderer :
	public Renderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void SetMesh(Mesh* mesh);

protected:
	virtual void OnMaterialUpdated(Material* oldMaterial, Material* newMaterial) override;

private:
	Mesh* m_mesh;
	MeshInfo* m_meshInfo;
};

