#pragma once

#include "Renderer.h"
#include "Mesh.h"


class MeshRenderer :
	public Renderer
{
public:
	MeshRenderer();
	virtual ~MeshRenderer() override;
	
	void SetMesh(Mesh mesh);
protected:

	virtual void OnMaterialUpdated(Material* oldMaterial, Material* newMaterial) override;

private:
	size_t m_meshIndex;
};

