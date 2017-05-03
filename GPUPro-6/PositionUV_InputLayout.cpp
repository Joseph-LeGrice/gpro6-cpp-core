#include "stdafx.h"
#include "PositionUV_InputLayout.h"


PositionUV_InputLayout::PositionUV_InputLayout()
{
	m_inputLayout = nullptr;
}

PositionUV_InputLayout::~PositionUV_InputLayout()
{
	SAFE_RELEASE(m_inputLayout);
}

bool PositionUV_InputLayout::CreateLayout(ID3D11Device* device, ID3D10Blob* vertexShaderBlob)
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	return device->CreateInputLayout(ied, 2, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_inputLayout) == S_OK;
}
