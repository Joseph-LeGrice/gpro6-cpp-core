#pragma once
#pragma warning(push)
#pragma warning(disable: 4127)

#include "D3D11.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"

enum BindFlags
{
	BIND_VERTEX = 1 << 0,
	BIND_HULL   = 1 << 1,
	BIND_DOMAIN = 1 << 2,
	BIND_GEOM   = 1 << 3,
	BIND_PIXEL  = 1 << 4,
	BIND_ALL    = BIND_VERTEX | BIND_HULL | BIND_DOMAIN | BIND_GEOM | BIND_PIXEL
};

class ConstantBuffer
{
friend class GraphicsSystem;
public:
	void UpdateBuffer(void* data, size_t length);
    void BindBuffer(UINT bufferSlot, BindFlags bindFlags);
    void ReleaseBuffer();

protected:
    void InitBuffer(UINT length);

private:
	GraphicsDevice& m_gfxDevice;
	ManualRelease<ID3D11Buffer> m_buffer;

	ConstantBuffer(GraphicsDevice& gfxDevice) :
		m_gfxDevice(gfxDevice) { }
	virtual ~ConstantBuffer();
};

#pragma warning(pop)