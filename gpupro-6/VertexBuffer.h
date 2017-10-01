#pragma once

#include "D3D11.h"
#include "PODArray.h"

struct VertexData;

class VertexBuffer
{
public:
	static VertexBuffer* Create(size_t bufferSize);
	~VertexBuffer();

	bool SetCurrentIfValid(); 
	bool TrySetData(PODArray<VertexData>& data);

private:
	VertexBuffer();

	ID3D11Buffer* m_vertexBuffer;
};

