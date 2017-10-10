#pragma once

#include "D3D11.h"

class ShaderResource
{
public:
	virtual ~ShaderResource();

	virtual ID3D11ShaderResourceView* GetResourceView() = 0;

protected:
	ShaderResource();

private:
	ShaderResource(const ShaderResource&) = delete;
};

