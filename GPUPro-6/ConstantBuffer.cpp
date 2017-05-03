#include "stdafx.h"
#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer()
{
}


ConstantBuffer::~ConstantBuffer()
{
}

ID3D11Buffer* ConstantBuffer::GetVSBuffer() { return nullptr; }
ID3D11Buffer* ConstantBuffer::GetHSBuffer() { return nullptr; }
ID3D11Buffer* ConstantBuffer::GetDSBuffer() { return nullptr; }
ID3D11Buffer* ConstantBuffer::GetGSBuffer() { return nullptr; }
ID3D11Buffer* ConstantBuffer::GetPSBuffer() { return nullptr; }