#pragma once

#include "D3D11.h"
#include "PODArray.h"
#include "VertexData.h"

class VertexBuffer
{
public:
	static VertexBuffer* Create(size_t bufferSize);
	~VertexBuffer();

	bool SetCurrentIfValid(); 
	void SetData(PODArray<VertexData>& data);

private:
	VertexBuffer();

	ID3D11Buffer* m_vertexBuffer;
};

