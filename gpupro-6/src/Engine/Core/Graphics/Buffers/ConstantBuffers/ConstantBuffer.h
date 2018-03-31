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

public:
    ConstantBuffer(GraphicsDevice& gfxDevice) :
        m_gfxDevice(gfxDevice) { }
    virtual ~ConstantBuffer();

    void BindBuffer();
    void ReleaseBuffer();

protected:
    virtual UINT GetBufferSlot() = 0;
    virtual BindFlags GetBindFlags() = 0;

    template<class T>
    void InitBuffer()
    {
        T initialData;
        ZeroMemory(&initialData, sizeof(T));

        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(T);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        D3D11_SUBRESOURCE_DATA data;
        ZeroMemory(&data, sizeof(data));
        data.pSysMem = &initialData;

        ID3D11Device* device = m_gfxDevice.GetGraphicsDevice();
        if (!SUCCEEDED(device->CreateBuffer(&desc, &data, m_buffer)))
        {
            LogError("[ConstantBuffer] Could not Create Buffer!");
        }
    }

    template<class T>
	void UpdateBuffer(const T& data)
	{
        static_assert(sizeof(T) % 16 == 0, "Constant Buffer size must be divisible by 16");
        static_assert(sizeof(T) <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT, "Constant Buffer size must be less than or equal to D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT");

		D3D11_MAPPED_SUBRESOURCE mappedData;
		ID3D11DeviceContext* deviceContext = m_gfxDevice.GetGraphicsDeviceContext();
		HRESULT bufferMapResult = deviceContext->Map(m_buffer, NULL, D3D11_MAP_WRITE_DISCARD, D3D11_USAGE_DEFAULT, &mappedData);
		if (SUCCEEDED(bufferMapResult))
		{
			memcpy(mappedData.pData, &data, sizeof(T));
			deviceContext->Unmap(m_buffer, 0);
		}
	}

private:
	GraphicsDevice& m_gfxDevice;
	ManualRelease<ID3D11Buffer> m_buffer;
};

#pragma warning(pop)