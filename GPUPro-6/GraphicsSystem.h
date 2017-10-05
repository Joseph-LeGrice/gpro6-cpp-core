#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#include <vector>
#include "GameSystem.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class Material;
class PerObjectConstantBuffer;
struct Camera;
struct SceneGraph;

class GraphicsSystem : public ISystem
{
	REGISTER_SUBSYSTEM(GraphicsSystem)

public:
	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();

	virtual void VariableTick() override;

	bool InitializeGraphics(HWND hwnd, int screenWidth, int screenHeight);
	float GetViewportWidth();
	float GetViewportHeight();

private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView * m_rtBackBuffer;

	PerObjectConstantBuffer* m_constantBuffer;

	float m_viewportWidth, m_viewportHeight;
};
