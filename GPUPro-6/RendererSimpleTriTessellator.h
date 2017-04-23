#pragma once
#include "Renderer.h"
class RendererSimpleTriTessellator :
	public Renderer
{
public:
	RendererSimpleTriTessellator();
	~RendererSimpleTriTessellator();

protected:
	Shader* RendererSimpleTriTessellator::InitShaders(ID3D11Device* device);
	Mesh* RendererSimpleTriTessellator::InitMesh(ID3D11Device* device);
};

