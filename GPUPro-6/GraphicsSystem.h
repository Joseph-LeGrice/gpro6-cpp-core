#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#include "GameSystem.h"
#include <vector>
#include "ISystem.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class SceneGraph;
class Material;
class ConstantBuffer;
class Camera;

class GraphicsSystem : public ISystem
{
	REGISTER_SUBSYSTEM(GraphicsSystem)

public:
	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();

	bool InitializeGraphics(HWND hwnd, int screenWidth, int screenHeight);

	void Render(Camera&, const std::vector<Material*>*);
	float GetViewportWidth();
	float GetViewportHeight();

private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView * m_rtBackBuffer;

	ConstantBuffer* m_constantBuffer;

	float m_viewportWidth, m_viewportHeight;
};
