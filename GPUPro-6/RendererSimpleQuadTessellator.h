#pragma once
#include "Renderer.h"
class RendererSimpleQuadTessellator :
	public Renderer
{
public:
	RendererSimpleQuadTessellator();
	~RendererSimpleQuadTessellator();

protected:
	virtual Shader* RendererSimpleQuadTessellator::InitShaders(ID3D11Device* device) override;
	virtual Mesh* RendererSimpleQuadTessellator::InitMesh(ID3D11Device* device) override;
	virtual ResourceViews* InitResourceViews(ID3D11Device* device) override;
	virtual ConstantBuffer* InitConstantBuffer(ID3D11Device* device) override;

private:
	InputLayout* m_inputLayout;
};

