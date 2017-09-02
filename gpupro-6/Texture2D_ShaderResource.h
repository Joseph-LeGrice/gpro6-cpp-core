#pragma once

#include "ShaderResource.h"
#include "D3D11.h"
#include <string>

class Texture2D_ShaderResource : ShaderResource
{
public:
	Texture2D_ShaderResource();
	~Texture2D_ShaderResource();

	static Texture2D_ShaderResource* CreateFromFile(std::wstring filepath);

	virtual bool Initialize() override;
	virtual ID3D11ShaderResourceView* GetResourceView() override;

private:
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_resourceView;
};

