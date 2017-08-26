#pragma once

#include "D3D11.h"

class ShaderResource
{
public:
	ShaderResource();
	~ShaderResource();

	virtual bool Initialize() = 0;
	virtual ID3D11ShaderResourceView* GetResourceView() = 0;

private:
	ShaderResource(const ShaderResource&);
};

