#pragma once

#include <vector>

struct ID3D11Buffer;
class GraphicsDevice;

const size_t INDEX_BUFFER_SIZE = (size_t)pow(1024, 2);

class IndexBuffer
{
public:
	IndexBuffer(GraphicsDevice* gfxDevice);
	IndexBuffer(const IndexBuffer& other) = delete;
	~IndexBuffer();

	bool SetCurrentIfValid();
	bool TrySetData(const std::vector<UINT16>& data);

private:
	GraphicsDevice* m_gfxDevice;
    AutoRelease<ID3D11Buffer> m_indexBuffer;
};
