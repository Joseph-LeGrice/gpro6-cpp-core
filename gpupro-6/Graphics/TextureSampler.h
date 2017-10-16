#pragma once

#include "D3D11.h"

class TextureSampler
{
	friend size_t CreateTextureSampler();
public:
	~TextureSampler();

	void BindTextureSampler(size_t samplerIndex, size_t numberOfSamplers);
	bool Initialize();
	bool IsValid();

private:
	ID3D11SamplerState* m_sampler;
	TextureSampler();
};

size_t CreateTextureSampler();