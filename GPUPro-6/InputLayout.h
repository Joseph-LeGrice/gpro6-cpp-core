#pragma once
#include "D3D11.h"

class InputLayout
{
public:
	InputLayout();
	~InputLayout();

	virtual bool CreateLayout(ID3D11Device* device, ID3D10Blob* vertexShaderBlob) = 0;
};

