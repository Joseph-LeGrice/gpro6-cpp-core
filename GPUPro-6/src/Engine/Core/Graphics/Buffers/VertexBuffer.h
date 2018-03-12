#pragma once

#include <vector>

struct VertexData;
struct ID3D11Buffer;
class GraphicsDevice;

const size_t VERTEX_BUFFER_SIZE = (size_t)pow(1024, 2);

class VertexBuffer
{
public:
	VertexBuffer(GraphicsDevice& gfxDevice);
	VertexBuffer(const VertexBuffer& other) = delete;
	~VertexBuffer();

	bool SetCurrentIfValid(); 
	bool TrySetData(const std::vector<VertexData>& data);

private:
	GraphicsDevice& m_gfxDevice;
	AutoRelease<ID3D11Buffer> m_vertexBuffer;
};

