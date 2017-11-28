#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#include <vector>
#include "SystemManagement/ISystem.h"

class Material;
class VertexBuffer;
class IndexBuffer;
struct Camera;

class GraphicsSystem : public ISystem
{
public:
	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();
    void SetDirty();

    GraphicsSystem();
    GraphicsSystem(const GraphicsSystem&) = delete;
    virtual ~GraphicsSystem();

    virtual bool Initialize() override;
    virtual void Deinitalize() override;
    virtual void VariableTick() override;

	float GetViewportWidth();
	float GetViewportHeight();

private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

#if defined(_DEBUG)
    ID3D11Debug* m_debugInterface;
#endif

	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView * m_rtBackBuffer;

	bool m_isDirty;
	VertexBuffer* m_myVertexBuffer;
	IndexBuffer* m_myIndexBuffer;

	float m_viewportWidth, m_viewportHeight;
	
	void UpdateIfDirty();
};
