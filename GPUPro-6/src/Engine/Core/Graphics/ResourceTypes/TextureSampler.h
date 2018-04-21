#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

struct ID3D11SamplerState;
class GraphicsDevice;


class TextureSampler : public IResource
{
DEFINE_RESOURCE(TextureSampler)
public:
	void BindTextureSampler(UINT samplerIndex);
	void Initialize() override;
	bool IsValid();

    virtual void Release() override;

private:
	ManualRelease<ID3D11SamplerState> m_sampler;
};
REGISTER_RESOURCE(TextureSampler, 6)
