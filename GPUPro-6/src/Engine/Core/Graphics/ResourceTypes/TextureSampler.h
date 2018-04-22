#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"


struct ID3D11SamplerState;
class GraphicsDevice;


class TextureSampler : public IResource
{
public:
	void BindTextureSampler(UINT samplerIndex);
	void Initialize() override;
	bool IsValid();

    virtual void Release() override;

	virtual const char* GetTypeName() override
	{
		return TO_STRING(TextureSampler);
	}

private:
	ManualRelease<ID3D11SamplerState> m_sampler;
};
REGISTER_TYPE(TextureSampler, 6)
