#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"

struct ID3D11SamplerState;
class GraphicsDevice;


class TextureSampler : public IResource
{
public:
	void BindTextureSampler(UINT samplerIndex);
	bool Initialize();
	bool IsValid();

    virtual void Release() override;
	static const RegisterResource<TextureSampler, 6> static_registration;

private:
	ManualRelease<ID3D11SamplerState> m_sampler;
};