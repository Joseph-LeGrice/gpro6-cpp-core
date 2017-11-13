#pragma once

#include "D3D11.h"

class TextureSampler
{
public:
	TextureSampler();
	~TextureSampler();

	void BindTextureSampler(UINT samplerIndex);
	bool Initialize();
	bool IsValid();

private:
	ID3D11SamplerState* m_sampler;
};