#pragma once

#include "Renderer.h"
#include "Mesh.h"


class MeshRenderer :
	public Renderer
{
	friend Entity;

public:
	void SetMesh(Mesh& mesh);

protected:
	virtual void OnMaterialUpdated(Material* oldMaterial, Material* newMaterial) override;

private:
	MeshInfo m_meshInfo;

	MeshRenderer();
	virtual ~MeshRenderer() override;
};

