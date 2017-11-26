#pragma once

#include "D3D11.h"
#include "AssetManagement/IResource.h"

class TextureSampler : public IResource
{
public:
	TextureSampler(UINT resourceId);
	~TextureSampler();

	void BindTextureSampler(UINT samplerIndex);
	bool Initialize();
	bool IsValid();

private:
	ID3D11SamplerState* m_sampler;
};