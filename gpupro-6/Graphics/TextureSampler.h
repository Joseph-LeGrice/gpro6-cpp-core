#pragma once

#include "D3D11.h"

class TextureSampler
{
	friend int CreateTextureSampler();
public:
	~TextureSampler();

	void BindTextureSampler(UINT samplerIndex, UINT numberOfSamplers);
	bool Initialize();
	bool IsValid();

private:
	ID3D11SamplerState* m_sampler;
	TextureSampler();
};

int CreateTextureSampler();