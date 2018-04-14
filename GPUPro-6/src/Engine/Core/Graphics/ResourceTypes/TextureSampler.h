#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"

struct ID3D11SamplerState;
class GraphicsDevice;


class TextureSampler : public IResource
{
public:
	void BindTextureSampler(UINT samplerIndex);
	bool Initialize();
	bool IsValid();

    virtual void Release() override;

	static ResourceTypeID GetResourceType()
	{
		return 6;
	}

private:
	ManualRelease<ID3D11SamplerState> m_sampler;
};