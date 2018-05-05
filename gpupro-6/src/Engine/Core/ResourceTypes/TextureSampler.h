#pragma once

#include "Engine/Core/RTTI/ITypedObject.h"
#include "d3d11.h"

struct ID3D11SamplerState;
class GraphicsDevice;


class TextureSampler : public ITypedObject
{
REGISTER_TYPE(TextureSampler);
public:
	void BindTextureSampler(UINT samplerIndex);
	bool IsValid();

	virtual void Establish() override;
    virtual void Finalize() override;

private:
	ManualRelease<ID3D11SamplerState> m_sampler;
};
