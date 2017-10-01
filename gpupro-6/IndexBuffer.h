#pragma once

#include "D3D11.h"
#include "PODArray.h"

class IndexBuffer
{
public:
	~IndexBuffer();

	static IndexBuffer* Create(size_t bufferSize);

	bool SetCurrentIfValid();
	void SetData(PODArray<UINT16>& data);

private:
	IndexBuffer();

	ID3D11Buffer* m_indexBuffer;
};

