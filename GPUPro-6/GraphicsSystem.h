#pragma once

#include "Renderer.h"

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class GraphicsSystem
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	bool Initialize(HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	void Render();

private:
	IDXGISwapChain* m_swapchain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView * m_rtBackBuffer;
	D3DXMATRIX m_projectionMatrix;

	Renderer* m_renderer;
};
