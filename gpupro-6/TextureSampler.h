#pragma once

#include "D3D11.h"

class TextureSampler
{
public:
	TextureSampler();
	~TextureSampler();

	bool Initialize();
	bool IsValid();
	ID3D11SamplerState* GetSampler();
private:
	ID3D11SamplerState* m_sampler;
};

