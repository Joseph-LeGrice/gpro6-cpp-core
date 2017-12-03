#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#include <vector>
#include "SystemManagement/ISystem.h"

class Material;
class VertexBuffer;
class IndexBuffer;
class DepthStencilBuffer;
class RasterizerState;
struct Camera;

class GraphicsSystem : public ISystem
{
public:
    IDXGISwapChain* GetSwapChain();
    ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();
    DepthStencilBuffer* GetDepthStencilBuffer();
    RasterizerState* GetRasterizerState();
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
    ManualRelease<ID3D11Device> m_device;
    ManualRelease<ID3D11DeviceContext> m_deviceContext;
    ManualRelease<IDXGISwapChain> m_swapchain;

#if defined(_DEBUG)
    ManualRelease<ID3D11Debug> m_debugInterface;
#endif

	bool m_isDirty;
    RasterizerState* m_rasterizerState;
	VertexBuffer* m_myVertexBuffer;
    DepthStencilBuffer* m_depthStencilBuffer;
	IndexBuffer* m_myIndexBuffer;

	float m_viewportWidth, m_viewportHeight;
	
	void UpdateIfDirty();
};
