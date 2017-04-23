#pragma once
#include "Renderer.h"
class RendererSimpleQuadTessellator :
	public Renderer
{
public:
	RendererSimpleQuadTessellator();
	~RendererSimpleQuadTessellator();

protected:
	Shader* RendererSimpleQuadTessellator::InitShaders(ID3D11Device* device);
	Mesh* RendererSimpleQuadTessellator::InitMesh(ID3D11Device* device);
};

