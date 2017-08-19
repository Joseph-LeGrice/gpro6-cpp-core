#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class SceneGraph;

class GraphicsSystem
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	const ID3D11Device* GetGraphicsDevice();
	const ID3D11DeviceContext* GetGraphicsDeviceContext();

	void Initialize(HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	void Render();

private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView * m_rtBackBuffer;
};
