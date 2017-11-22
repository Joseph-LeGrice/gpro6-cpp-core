#pragma once

#include "D3D11.h"
#include <string>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

    void BindResource(UINT resourceIndex);

    static int CreateTextureResourceFromFile(const wchar_t* filepath);

private:
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_resourceView;
};
