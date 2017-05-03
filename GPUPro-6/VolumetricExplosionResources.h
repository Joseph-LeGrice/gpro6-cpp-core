#pragma once
#include "ResourceViews.h"

class VolumetricExplosionResources : public ResourceViews
{
public:
	VolumetricExplosionResources();
	~VolumetricExplosionResources();

	virtual bool Initialize(ID3D11Device* device) override;
	virtual std::vector<ID3D11ShaderResourceView *>* GetPSResources() override;

private:
	std::vector<ID3D11ShaderResourceView*>* m_resources;
	ID3D11Texture3D* m_pTexture;
};

