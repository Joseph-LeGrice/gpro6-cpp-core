#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"

struct ID3D11SamplerState;
class GraphicsDevice;

class TextureSampler : public IResource
{
public:
    TextureSampler(GraphicsDevice* gfxDevice, UINT ai) : IResource(ai), m_gfxDevice(gfxDevice) { }
    TextureSampler();
    ~TextureSampler();

	void BindTextureSampler(UINT samplerIndex);
	bool Initialize();
	bool IsValid();

    virtual void Release() override;

private:
	GraphicsDevice* m_gfxDevice;
	ManualRelease<ID3D11SamplerState> m_sampler;
};