#pragma once
#include "Renderer.h"
#include "InputLayout.h"

class RendererSimpleTexturedQuad :
	public Renderer
{
public:
	RendererSimpleTexturedQuad();
	~RendererSimpleTexturedQuad();
protected:
	virtual Shader* InitShaders(ID3D11Device* device) override;
	virtual Mesh* InitMesh(ID3D11Device* device) override;
private:
	bool InitTexture(ID3D11Device* device, Mesh* m);

	ID3D11ShaderResourceView* m_shaderResourceView;
	ID3D11Texture2D* m_pTexture;
	InputLayout* m_inputLayout;
};

