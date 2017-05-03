#pragma once
#include "Renderer.h"
#include "InputLayout.h"

class RendererSimpleTriTessellator :
	public Renderer
{
public:
	RendererSimpleTriTessellator();
	~RendererSimpleTriTessellator();

protected:
	Shader* RendererSimpleTriTessellator::InitShaders(ID3D11Device* device);
	Mesh* RendererSimpleTriTessellator::InitMesh(ID3D11Device* device);

private:
	InputLayout* m_inputLayout;
};

