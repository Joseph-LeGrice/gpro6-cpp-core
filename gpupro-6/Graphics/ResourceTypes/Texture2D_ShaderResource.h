#pragma once

#include "ShaderResource.h"
#include "D3D11.h"
#include <string>

class Texture2D_ShaderResource : ShaderResource
{
	friend size_t CreateTextureResourceFromFile(std::wstring filepath);
public:
	virtual ~Texture2D_ShaderResource() override;
protected:
	virtual ID3D11ShaderResourceView* GetResourceView() override;

private:
	Texture2D_ShaderResource();

	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_resourceView;
};

size_t CreateTextureResourceFromFile(std::wstring filepath);