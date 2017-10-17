#pragma once

#include "D3D11.h"
#include "DataStructures\PODArray.h"

class IndexBuffer
{
public:
	~IndexBuffer();

	static IndexBuffer* Create(size_t bufferSize);

	bool SetCurrentIfValid();
	bool TrySetData(const std::vector<UINT16>& data);

private:
	IndexBuffer();

	ID3D11Buffer* m_indexBuffer;
};

