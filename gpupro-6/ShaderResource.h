#pragma once

#include "D3D11.h"

class ShaderResource
{
public:
	ShaderResource();
	~ShaderResource();

	virtual ID3D11ShaderResourceView* GetResourceView() = 0;

private:
	ShaderResource(const ShaderResource&);
};

