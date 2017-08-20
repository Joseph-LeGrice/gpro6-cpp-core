#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#include <vector>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class SceneGraph;
class Material;

class GraphicsSystem
{
public:
	~GraphicsSystem();

	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();

	static GraphicsSystem* InitializeGraphics(HWND hwnd, int screenWidth, int screenHeight);

	void Render(const std::vector<Material*>*);

private:
	GraphicsSystem(ID3D11Device* gfxDevice, ID3D11DeviceContext* gfxDeviceContext, IDXGISwapChain* gfxSwapChain, ID3D11RenderTargetView* gfxBackBuffer) :
		m_device(gfxDevice), m_deviceContext(gfxDeviceContext), m_swapchain(gfxSwapChain), m_rtBackBuffer(gfxBackBuffer) { }
	
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView * m_rtBackBuffer;
};
