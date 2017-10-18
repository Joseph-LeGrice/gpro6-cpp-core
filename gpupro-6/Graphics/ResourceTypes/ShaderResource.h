#pragma once

#include "D3D11.h"

class ShaderResource
{
public:
	virtual ~ShaderResource();

	void BindResource(UINT resourceIndex);

protected:
	ShaderResource();
	virtual ID3D11ShaderResourceView* GetResourceView() = 0;

private:
	ShaderResource(const ShaderResource&) = delete;
};

