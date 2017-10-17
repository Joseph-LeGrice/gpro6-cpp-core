#pragma once

#include "D3D11.h"

class ShaderResource
{
public:
	virtual ~ShaderResource();

	void BindResource(size_t resourceIndex, size_t numberOfResources);

protected:
	ShaderResource();
	virtual ID3D11ShaderResourceView* GetResourceView() = 0;

private:
	ShaderResource(const ShaderResource&) = delete;
};

