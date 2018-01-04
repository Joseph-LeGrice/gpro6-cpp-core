#pragma once

#include "D3D11.h"
#include <vector>

class IndexBuffer
{
public:
	~IndexBuffer();

	static IndexBuffer* Create(size_t bufferSize);

	bool SetCurrentIfValid();
	bool TrySetData(const std::vector<UINT16>& data);

private:
	IndexBuffer();

    AutoRelease<ID3D11Buffer> m_indexBuffer;
};

