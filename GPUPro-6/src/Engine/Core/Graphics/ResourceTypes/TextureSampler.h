#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"

struct ID3D11SamplerState;
class GraphicsDevice;
class ResourceReferences;

class TextureSampler : public IResource
{
public:
    TextureSampler(size_t resourceIndex, ResourceReferences& resourceReferences) :
		IResource(resourceIndex, resourceReferences) { }

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