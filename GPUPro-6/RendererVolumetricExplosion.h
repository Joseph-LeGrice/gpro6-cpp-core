#pragma once
#include "Renderer.h"
class RendererVolumetricExplosion :
	public Renderer
{
public:
	RendererVolumetricExplosion();
	~RendererVolumetricExplosion();

protected:
	virtual Shader* InitShaders(ID3D11Device* device) override;
	virtual Mesh* InitMesh(ID3D11Device* device) override;
};

