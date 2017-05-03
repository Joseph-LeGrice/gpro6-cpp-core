#pragma once
#include "InputLayout.h"

class PositionUV_InputLayout : public InputLayout
{
public:
	PositionUV_InputLayout();
	~PositionUV_InputLayout();

	virtual bool CreateLayout(ID3D11Device* device, ID3D10Blob* vertexShaderBlob) override;

private:
	ID3D11InputLayout* m_inputLayout;
};

