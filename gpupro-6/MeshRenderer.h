#pragma once

#include "Renderer.h"
#include "Mesh.h"


class MeshRenderer :
	public Renderer
{
	friend Entity;

public:
	void SetMesh(Mesh& mesh);

	virtual void Tick() override;

protected:
	MeshRenderer();

	virtual void OnMaterialUpdated(Material* oldMaterial, Material* newMaterial) override;

private:
	MeshInfo m_meshInfo;

	virtual ~MeshRenderer() override;
};

